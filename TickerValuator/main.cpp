#include <iostream>
#include "tbb/concurrent_vector.h"
#include <fstream>

#include "ticker.h"
#include "ticker_storage.h"
#include "simplified_ticker.h"
#include "area_utils.h"
#include "file_manager.h"
#include <dirent.h>
#include "tbb/parallel_for.h"
#include <cmath>
#include <chrono>


typedef tbb::concurrent_unordered_map<std::string, std::pair<tbb::concurrent_vector<ticker>::iterator, tbb::concurrent_vector<ticker>::iterator>> MySymbolMap;

string output_path;
unsigned long max_size;

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
    const int index = order * 2 + 1;
    string current_flag = argv[index];

    //Choose path type
    if (current_flag == "-i") {

        filename = argv[index + 1];
        return true;

    } else if (current_flag == "-o") {

        output_path = argv[index + 1];
        return true;

    } else {
        cerr << "Wrong arguments, please use -i <filename> or -o <path>" << endl;
        return false;

    }
}


tbb::concurrent_vector<simplified_ticker> get_print_ready_vector(unsigned long max_size,
                                                                 const tbb::concurrent_vector<ticker>::iterator &first_ticker_it,
                                                                 const tbb::concurrent_vector<ticker>::iterator &last_ticker_it) {
    tbb::concurrent_vector<simplified_ticker> printing_vector;
    printing_vector.reserve(max_size);
    // current ticker will represent the currently evaluated ticker
    auto current_ticker_it = first_ticker_it;

    // a pointer to the next ticker and the previous is kept for reference
    auto previous_ticker_it = current_ticker_it;
    auto next_ticker_it = std::next(current_ticker_it, 1);

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
        if (next_ticker_it != last_ticker_it && current_ticker == next_ticker) {
            // Add price to pricing set (this will average later)
            next_ticker.add_price(current_ticker.price(), current_ticker.price_nr());
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
                        std::floor(current_ticker.seconds()), current_ticker.seconds(), current_ticker.avg_price(),
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
                        std::floor(current_ticker.seconds()) + 1,
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
            std::advance(current_ticker_it, 1);
            // prevent weird iterator bugs...
            if (current_ticker_it != last_ticker_it) {
                next_ticker_it = std::next(current_ticker_it, 1);
            }
        }

    }
    printing_vector.shrink_to_fit();
    return printing_vector;
}

class SymbolMapIteration {

    MySymbolMap &data;

public:

    SymbolMapIteration(MySymbolMap &_data) : data(_data) {}

    void operator()(MySymbolMap::range_type &r) const {

        for (MySymbolMap::iterator current_symbol = r.begin(); current_symbol != r.end(); ++current_symbol) {

            auto first_ticker_it = current_symbol->second.first;
            auto last_ticker_it = current_symbol->second.second;

            tbb::concurrent_vector<simplified_ticker> printing_vector = get_print_ready_vector(max_size,
                                                                                               first_ticker_it,
                                                                                               last_ticker_it);

            file_manager fm = file_manager();
            fm.file_writer(output_path, current_symbol->first, printing_vector);
        }
    }
};

void print_processed_list(const ticker_storage &ts) {


    max_size = ts.ticker_vector().size();

    MySymbolMap mySymbolMap = ts.classifying_map();

    MySymbolMap::range_type r = mySymbolMap.range();

    tbb::parallel_for(r, SymbolMapIteration(mySymbolMap), tbb::auto_partitioner());
}

int main(int argc, char **argv) {
    std::chrono::time_point<std::chrono::high_resolution_clock> time_start = std::chrono::high_resolution_clock::now();

    using namespace std;
    string filename;
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

    if (!output_path.empty()) {

        DIR *dir = opendir(output_path.c_str());
        if (dir) {
            closedir(dir);
        } else {
            cerr << "Directory " << output_path << " does not exist." << endl;
        }
    }

    if (filename.empty()) {
        ts = manual_ticker_insertion();
    } else {
        ts = fm.file_reader(filename);
    }

    // ** Process Ticker List **
    // 1. Sort ticker based on symbol, date and time
    ts.sort_ticker();

    // 2. Classify based on symbol
    // Final structure is:
    // Map<Symbol, { beginning iterator, end iterator } >
    ts.symbol_classify();

    // 3. Initialize vector to print ticker's
    // 4. calculate areas
    print_processed_list(ts);
    
    auto time_print_file = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_print_time = time_print_file - time_start;
    std::cout << "Print time: " << duration_print_time.count() << " s\n";

}
