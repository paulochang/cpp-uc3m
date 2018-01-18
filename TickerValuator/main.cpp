#include <iostream>
#include <vector>
#include <fstream>

#include "ticker.h"
#include "ticker_storage.h"
#include "simplified_ticker.h"
#include "area_utils.h"
#include "file_manager.h"


bool manual_ticker_insertion();

/// Manual ticker insertion
/// \param ts a ticker_storage object
/// \return true if at least one ticker was inserted
bool manual_ticker_insertion(ticker_storage ts) {

    cout << "Insert tickers: " << endl;

    cin.exceptions(cin.exceptions() | ios_base::failbit);
    ticker tk;

    while (cin >> tk) {
        ts.add_ticker(tk);
    }

    return ts.ticker_vector().size() > 0;
}

bool set_input_arg(char **argv, std::string &filename, std::string &output_path, int order) {
    string current_flag = argv[order];

    //Choose path type
    if (current_flag == "-i") {

        filename = argv[order * 2 + 1];
        return true;

    } else if (current_flag == "-o") {

        output_path = argv[order * 2 + 1];
        return true;

    } else {
        cerr << "Wrong arguments, please use -i <filename> or -o <path>" << endl;
        return false;

    }
}

int main(int argc, char **argv) {
    using namespace std;

    string filename;
    string output_path;
    file_manager fm = file_manager();

    // INITIALIZE TICKER_STORAGE
    ticker_storage ts = ticker_storage();

    //region **Argument Handling**
    // Handle different arg numbers
    switch (argc) {
        // no arguments
        case 1 : {
            manual_ticker_insertion(ts);
            break;
        }
            // one argument
        case 3 : {
            set_input_arg(argv, filename, output_path, 0);
            fm.file_reader(filename);
            break;
        }
            // two arguments
        case 5 : {
            set_input_arg(argv, filename, output_path, 0);
            set_input_arg(argv, filename, output_path, 1);
            fm.file_reader(filename);
            break;
        }
            // invalid argument nr.
        default: {
            cerr << "Wrong arguments" << endl;
            cerr << "Valid formats: " << endl;
            cerr << "-i <filename>" << endl;
            cerr << "-o <path>" << endl;
            cerr << "-i <filename> -o <path>" << endl;
            return -1;
        }
    }
    //endregion

    // ** Process Ticker List **
    // 1. Sort ticker based on symbol, date and time
    ts.sort_ticker();

    //region DEBUG - DISPLAY SORTED VECTOR
    /*
    std::cout << "Sorted ticker vector:" << endl;
    for (const auto &i: ts.ticker_vector()) {
        std::cout << i << endl;
    }
     */
    //endregion

    // 2. Classify based on symbol
    // Final structure is:
    // Map<Symbol, { beginning iterator, end iterator } >
    ts.symbol_classify();

    // 3. Initialize vector to print ticker's
    std::vector<simplified_ticker> printing_vector;
    printing_vector.reserve(ts.ticker_vector().size());

    //region DEBUG - TICKER CLASSIFYING MAP
    //std::cout << "ticker classifying map:" << endl;
    //endregion
    // For each asset...
    for (auto current_symbol : ts.classifying_map()) {
        //region DEBUG - DISPLAY CURRENT GROUP
        //std::cout << "Current group: " << current_symbol.first << endl;
        //endregion
        auto first_ticker_it = current_symbol.second.first;
        auto last_ticker_it = current_symbol.second.second;

        auto current_ticker_it = first_ticker_it;

        auto previous_ticker_it = current_ticker_it;
        auto next_ticker_it = current_ticker_it + 1;

        double current_area = 0;

        bool previous_in_range = false;

        while (current_ticker_it != last_ticker_it) {
            ticker current_ticker = (*current_ticker_it);
            ticker previous_ticker = (*previous_ticker_it);
            ticker next_ticker = (*next_ticker_it);

            if (current_ticker == next_ticker) {
                next_ticker.add_price(current_ticker.price());
                current_ticker_it = next_ticker_it++;
            } else {
                if (!previous_in_range) {
                    current_area += AreaUtils::left_area(
                            floor(current_ticker.seconds()), current_ticker.seconds(), current_ticker.avg_price(),
                            current_ticker.avg_price());
                } else {
                    current_area += AreaUtils::left_area(
                            previous_ticker.seconds(), current_ticker.seconds(), previous_ticker.avg_price(),
                            current_ticker.avg_price());
                }
                if (AreaUtils::isContiguous(current_ticker, next_ticker)) {
                    previous_in_range = true;
                } else {
                    current_area += AreaUtils::right_area(
                            current_ticker.seconds(),
                            floor(current_ticker.seconds()) + 1,
                            current_ticker.avg_price(),
                            current_ticker.avg_price());

                    previous_in_range = false;
                    printing_vector.push_back(
                            simplified_ticker(current_ticker.date(), current_ticker.time(), current_area));
                }
                previous_ticker_it = current_ticker_it;
                current_ticker_it++;
                next_ticker_it = current_ticker_it + 1;
            }

        }

    }
}
