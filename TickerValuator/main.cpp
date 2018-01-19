#include <iostream>
#include <vector>
#include <fstream>

#include "ticker.h"
#include "ticker_storage.h"
#include "simplified_ticker.h"
#include "area_utils.h"
#include "file_manager.h"


/// Manual ticker insertion
/// \return ts a ticker_storage object
ticker_storage manual_ticker_insertion() {

    cout << "Insert tickers: " << endl;

    ticker_storage ts;
    cin.exceptions(cin.exceptions() | ios_base::failbit);
    ticker tk;

    while (cin >> tk) {
        ts.add_ticker(tk);
    }

    return ts;
}

bool set_input_arg(char **argv, std::string &filename, std::string &output_path, const int order) {
    const int index = order*2+1;
    string current_flag = argv[index];

    //Choose path type
    if (current_flag == "-i") {

        filename = argv[index+1];
        return true;

    } else if (current_flag == "-o") {

        output_path = argv[index+1];
        return true;

    } else {
        cerr << "Wrong arguments, please use -i <filename> or -o <path>" << endl;
        return false;

    }
}


std::vector<simplified_ticker> get_print_ready_vector(unsigned long max_size,
                                                      const __wrap_iter<vector<ticker, std::__1::allocator<ticker>>::pointer> &first_ticker_it,
                                                      const __wrap_iter<vector<ticker, std::__1::allocator<ticker>>::pointer> &last_ticker_it) {
    vector<simplified_ticker> printing_vector;
    printing_vector.reserve(max_size);
    // current ticker will represent the currently evaluated ticker
    auto current_ticker_it = first_ticker_it;

    // a pointer to the next ticker and the previous is kept for reference
    auto previous_ticker_it = current_ticker_it;
    auto next_ticker_it = current_ticker_it + 1;

    // this will be the area cummulative variable
    double current_area = 0;
    // this flag is true when the previous ticker was within the same timeframe
    bool previous_in_range = false;

    //1. iterate through tickers
    while (current_ticker_it != last_ticker_it) {
        ticker current_ticker = (*current_ticker_it);
        ticker previous_ticker = (*previous_ticker_it);
        ticker next_ticker = (*next_ticker_it);

        // CASE1: next ticker has same timestamp (and symbol) as previous
        if (current_ticker == next_ticker) {
            // Add price to pricing set (this will average later)
            next_ticker.add_price(current_ticker.price());
            current_ticker_it = next_ticker_it++;
        } else {

            //CASE2: next ticker has different timestamp as previous
            // Area creation has two parts:

            //region ** Area to the left calculation **
            if (!previous_in_range) {
                //CASE 2.1: previous ticker was in different minute timeframe

                // Since previous ticker was not in the same minute timeframe, this is the first ticker
                // therefore, calculate area to the left pretending lower bound has same price and keep going
                current_area += AreaUtils::left_area(
                        floor(current_ticker.seconds()), current_ticker.seconds(), current_ticker.avg_price(),
                        current_ticker.avg_price());
            } else {
                //CASE 2.2: previous ticker was in same minute timeframe

                // Otherwise, calculate area to the left with the previous ticker price and keep going
                current_area += AreaUtils::left_area(
                        previous_ticker.seconds(), current_ticker.seconds(), previous_ticker.avg_price(),
                        current_ticker.avg_price());
            }
            //endregion

            //region ** Area to the right calculation **
            if (next_ticker_it != last_ticker_it && AreaUtils::isContiguous(current_ticker, next_ticker)) {
                //CASE 2.a: if there is at least one remaining ticker
                // AND it's in the same timeframe as current one
                // enable previous_in_range flag
                previous_in_range = true;
            } else {
                //CASE 2.b: if not, just assume limit of timeframe has the same value and sum up area.
                current_area += AreaUtils::right_area(
                        current_ticker.seconds(),
                        floor(current_ticker.seconds()) + 1,
                        current_ticker.avg_price(),
                        current_ticker.avg_price());

                // reset area summation and flags, send to printer
                previous_in_range = false;
                printing_vector.push_back(
                        simplified_ticker(current_ticker.date(), current_ticker.time(), current_area));
                current_area = 0;
            }
            //endregion

            // recalculate iterators
            previous_ticker_it = current_ticker_it;
            current_ticker_it++;
            // prevent weird iterator bugs...
            if (current_ticker_it != last_ticker_it) {
                next_ticker_it = current_ticker_it + 1;
            }
        }

    }
    return printing_vector;
}

void print_processed_list(const string output, const ticker_storage &ts, const file_manager fm) {


    unsigned long max_size = ts.ticker_vector().size();


    // For each asset...
    for (auto current_symbol : ts.classifying_map()) {

        auto first_ticker_it = current_symbol.second.first;
        auto last_ticker_it = current_symbol.second.second;

        std::vector<simplified_ticker> printing_vector = get_print_ready_vector(max_size, first_ticker_it,
                                                                                last_ticker_it);
        fm.file_writer(output, current_symbol.first, printing_vector);
    }
}

int main(int argc, char **argv) {
    using namespace std;

    string filename;
    string output_path = "";
    file_manager fm = file_manager();

    // INITIALIZE TICKER_STORAGE
    ticker_storage ts = ticker_storage();

    //region **Argument Handling**
    // Handle different arg numbers
    switch (argc) {
        // no arguments
        case 1 : {
            break;
        }
            // one argument
        case 3 : {
            set_input_arg(argv, filename, output_path, 0);
            break;
        }
            // two arguments
        case 5 : {
            set_input_arg(argv, filename, output_path, 0);
            set_input_arg(argv, filename, output_path, 1);
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

    if (filename.empty()){
        ts = manual_ticker_insertion();
    } else {
        ts = fm.file_reader(filename);
    }

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

    // 4. calculate areas
    //region DEBUG - TICKER CLASSIFYING MAP
    //std::cout << "ticker classifying map:" << endl;
    //endregion

    print_processed_list(output_path, ts, fm);
}
