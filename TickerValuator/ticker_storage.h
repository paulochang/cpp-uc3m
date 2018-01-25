//
// Created by Paulo Chang on 1/6/18.
//

#ifndef TICKERVALUATOR_TICKER_STORAGE_H
#define TICKERVALUATOR_TICKER_STORAGE_H

#include <unordered_set>
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include "tbb/concurrent_vector.h"


#include "ticker.h"

class ticker_storage {
public:
    void add_ticker(const ticker &myTicker);

    void sort_ticker();

    void symbol_classify();

    const std::unordered_map<std::string, std::pair<tbb::concurrent_vector<ticker>::iterator, tbb::concurrent_vector<ticker>::iterator>> &
    classifying_map() const;

    const tbb::concurrent_vector<ticker> &ticker_vector() const;

private:
    tbb::concurrent_vector<ticker> ticker_vector_;
    std::unordered_set<std::string> symbol_set_;
    std::unordered_map<std::string, std::pair<tbb::concurrent_vector<ticker>::iterator, tbb::concurrent_vector<ticker>::iterator>> classifying_map_;
    bool is_sorted{false};
};

#endif //TICKERVALUATOR_TICKER_STORAGE_H
