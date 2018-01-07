//
// Created by Paulo Chang on 1/6/18.
//

#ifndef TICKERVALUATOR_TICKER_STORAGE_H
#define TICKERVALUATOR_TICKER_STORAGE_H

#include <vector>
#include <unordered_set>
#include <string>
#include "ticker.h"

class ticker_storage {
public:
    void add_ticker(ticker myTicker);
    void sort_ticker();
private:
    std::vector<ticker> ticker_set_;
    std::unordered_set<std::string> symbol_set_;
};

#endif //TICKERVALUATOR_TICKER_STORAGE_H
