#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <stdexcept>

#include "ticker.h"
#include "ticker_storage.h"
#include "simplified_ticker.h"
#include "area_utils.h"
#include "file_manager.h"


int main(int argc, char ** argv) {
    using namespace std;

    string input_path;
    string output_path;
    file_manager fm = file_manager();

    // Default arguments
    if (argc == 1 ) {

        cout << "Insert tickers: " << endl;
        
        cin.exceptions(cin.exceptions() | ios_base::failbit);
        ticker tk;
        ticker_storage ts = ticker_storage();
        
        while (cin >> tk){
            ts.add_ticker(tk);
        }

        ts.sort_ticker();

    // One argument, input or output path
    } else if (argc == 3){

        string argv1 = argv[1];

        // Verify input or output
        if (argv1 == "-i"){

        input_path = argv[2];
        fm.file_reader(input_path);

        } else if (argv1 == "-o"){

        output_path = argv[2];
        //fm.file_writer(output_path);

        } else{

        cerr << "Wrong arguments, please use -i <filename> or -o <path>" << endl;
        return -1;

        }

    // Both arguments, input and output path
    } else if (argc == 5){

        string argv1 = argv[1];
        string argv3 = argv[3];

        // Set input and output paths
        if (argv1 == "-i"){

        if (argv3 == "-o"){

            input_path = argv[2];
            output_path = argv[4];

            fm.file_reader(input_path);
            //fm.file_writer(output_path);

        }

        } else if (argv1 == "-o"){

        if (argv3 == "-i"){

            input_path = argv[4];
            output_path = argv[2];

            fm.file_reader(input_path);
            //fm.file_writer(output_path);

        }

        } else{

        cerr << "Wrong arguments, please use -i <filename> and -o <path>" << endl;
        return -1;

        }

    // Error
    } else{

        cerr << "Wrong arguments" << endl;
        cerr << "Valid formats: " << endl;
        cerr << "-i <filename>" << endl;
        cerr << "-o <path>" << endl;
        cerr << "-i <filename> -o <path>" << endl;
        return -1;
    }



    cout << __cplusplus << endl;

    
    ticker_storage ts = ticker_storage();
    
    /*
    ticker a1 = ticker(1012001, 1200, 23.3242, "APPL", 803.20);
    ticker a2 = ticker(1012000, 1200, 23.3242, "APPL", 803.20);
    ticker a3 = ticker(1012000, 1201, 23.3242, "APPL", 803.20);
    ticker a4 = ticker(1012000, 1202, 23.3242, "APPL", 803.20);
    ticker a5 = ticker(1012000, 1202, 23.3042, "APPL", 803.20);
    ticker g1 = ticker(1012000, 1200, 23.3242, "GOOGL", 803.20);
    ts.add_ticker(a1);
    ts.add_ticker(a2);
    ts.add_ticker(a5);
    ts.add_ticker(a4);
    ts.add_ticker(a3);
    ts.add_ticker(g1);
    */

    std::cout << "Sorted ticker vector:" << endl;
    for (const auto &i: ts.ticker_vector()) {
        std::cout << i << endl;
    }

    ts.symbol_classify();

    std::vector<simplified_ticker> printing_vector;
    printing_vector.reserve(ts.ticker_vector().size());

    std::cout << "ticker classifying map:" << endl;
    for (auto current_symbol : ts.classifying_map()) {

        std::cout << "Current group: " << current_symbol.first << endl;

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
        /*
        bool has_contiguous_neighbor = false;
        bool is_first = true;
        auto previous_ticker = current_ticker_it;
        auto next_ticker = current_ticker_it+1;
        double current_area = 0.0;

        while (current_ticker_it != last_ticker_it) {
            std::cout << " " << (*current_ticker_it) << endl;
            if (is_first) {
                if (!AreaUtils::isContiguous((*current_ticker_it).seconds(), (*next_ticker).seconds())) {
                    printing_vector.
                            push_back(simplified_ticker((*current_ticker_it).date(),
                                                        (*current_ticker_it).time(),
                                                        (*current_ticker_it).avg_price()));
                } else {
                    current_area = AreaUtils::area(floor((*current_ticker_it).seconds()),
                                                   (*current_ticker_it).seconds(),
                                                   (*current_ticker_it).avg_price(),
                                                   (*current_ticker_it).avg_price());
                    has_contiguous_neighbor = true;
                }
                is_first = false;
            } else {

            }

            previous_ticker = current_ticker_it;
            next_ticker = ++current_ticker_it;

        }

        */

        //verificar que el siguiente no es el mismo punto
        // si es el mismo, darle push a los precios y mover el pointer actual al siguiente
        // si no es mismo, verificar si está en mismo rango
        // si está en mismo rango,
        // si tenía vecino,
        // calcular area con anterior
        // marcar como vecino
        // si no es contiguo

    }
}