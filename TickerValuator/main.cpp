#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "ticker_storage.h"

int main() {
    using namespace std;
    cout << __cplusplus << endl;

    ticker_storage ts = ticker_storage();
    ticker t = ticker(01012001,1200,23.3242,"APPL", 803.20);
    ts .add_ticker(t);
    ts.sort_ticker();
    ts.classify();
    return 0;
}