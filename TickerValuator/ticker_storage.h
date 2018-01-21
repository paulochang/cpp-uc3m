//
// Created by Paulo Chang on 1/6/18.
//

#ifndef TICKERVALUATOR_TICKER_STORAGE_H
#define TICKERVALUATOR_TICKER_STORAGE_H

#include <unordered_set>
#include <string>
#include <unordered_map>
#include <vector>
#include "ticker.h"

class ticker_storage {
public:
    void add_ticker(ticker myTicker);

    void sort_ticker();

    void symbol_classify();

    const std::unordered_map<std::string, std::pair<std::vector<ticker>::iterator, std::vector<ticker>::iterator>> &
    classifying_map() const;

    const std::vector<ticker> &ticker_vector() const;

private:
    std::vector<ticker> ticker_vector_;
    std::unordered_set<std::string> symbol_set_;
    std::unordered_map<std::string, std::pair<std::vector<ticker>::iterator, std::vector<ticker>::iterator>> classifying_map_;
    bool is_sorted{false};
    bool is_classified{false};
};

#endif //TICKERVALUATOR_TICKER_STORAGE_H
