//
// Created by Paulo Chang on 1/6/18.
//

#ifndef TICKERVALUATOR_TICKER_STORAGE_H
#define TICKERVALUATOR_TICKER_STORAGE_H

#include <vector>
#include <unordered_set>
#include <string>
#include <unordered_map>
#include "ticker.h"

class ticker_storage {
public:
    void add_ticker(ticker myTicker);
    void sort_ticker();
    void classify();

    const std::unordered_map<std::string, std::pair<std::__wrap_iter<std::vector<ticker, std::__1::allocator<ticker>>::pointer>, std::__wrap_iter<std::vector<ticker, std::__1::allocator<ticker>>::pointer>>> &
    getClassifying_map_() const;

private:
    std::vector<ticker> ticker_vector_;
    std::unordered_set<std::string> symbol_set_;
    std::unordered_map<std::string, std::pair<std::vector<ticker>::iterator,std::vector<ticker>::iterator>> classifying_map_;
    bool is_sorted {false};
    bool is_classified {false};
};

#endif //TICKERVALUATOR_TICKER_STORAGE_H
