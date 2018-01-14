#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "ticker.h"
#include "ticker_storage.h"

int main() {
    using namespace std;
    cout << __cplusplus << endl;

    ticker_storage ts = ticker_storage();
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

    std::cout << "Sorted ticker vector:" << endl;
    for (const auto &i: ts.ticker_vector()) {
        std::cout << i << endl;
    }

    ts.symbol_classify();


    std::cout << "Holi: " << a1 << endl;
    std::cout << "ticker classifying map:" << endl;


    for (auto current_symbol : ts.classifying_map()) {
        std::cout << "Current group: " << current_symbol.first << endl;
        auto first_ticker_it = current_symbol.second.first;
        auto last_ticker_it = current_symbol.second.second;
        auto current_ticker_it = first_ticker_it;
        while (current_ticker_it != last_ticker_it) {
            std::cout << " " << (*current_ticker_it) << endl;
            current_ticker_it++;
        }
    }


    return 0;
}