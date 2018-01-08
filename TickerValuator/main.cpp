#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "ticker_storage.h"

int main() {
    using namespace std;
    cout << __cplusplus << endl;

    ticker_storage ts = ticker_storage();
    ticker t1 = ticker(1012001,1200,23.3242,"APPL", 803.20);
    ticker t2 = ticker(1012000,1200,23.3242,"APPL", 803.20);
    ticker t3 = ticker(1012000,1200,23.3242,"GOOGL", 803.20);
    ts.add_ticker(t1);
    ts.add_ticker(t2);
    ts.add_ticker(t3);
    ts.sort_ticker();

    std::cout << "Sorted Ticker vector:" << endl;
    for (auto i: ts.getTicker_vector_()) {
        std::cout << i.to_string() << endl;
    }

    ts.classify();

    std::cout << "Ticker classifying map:" << endl;

    for(auto i : ts.getClassifying_map_()) {
        for ( auto it = i.second.first; it != i.second.second; ++it )
            std::cout << " " << it.base()->to_string() << endl;
    }

    return 0;
}