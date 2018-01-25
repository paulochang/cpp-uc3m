//
// Created by Paulo Chang on 1/6/18.
//
#ifdef _MSC_VER
#include <iso646.h>
#endif
#include "ticker_storage.h"

struct SymbolComparer {
    bool operator()(const ticker &s, const std::string &i) {
        return s.symbol() < i;
    }

    bool operator()(const std::string &i, const ticker &s) {
        return i < s.symbol();
    }
};

void ticker_storage::add_ticker(const ticker &myTicker) {
    is_sorted = false;
    ticker_vector_.push_back(myTicker);
    symbol_set_.insert(myTicker.symbol());
}

void ticker_storage::sort_ticker() {
    std::sort(ticker_vector_.begin(), ticker_vector_.end());
    is_sorted = true;
}

void ticker_storage::symbol_classify() {
    if (!is_sorted) sort_ticker();
    for (const auto &i : symbol_set_) {
        this->classifying_map_.insert(
                make_pair(i, std::equal_range(ticker_vector_.begin(), ticker_vector_.end(), i, SymbolComparer())));
    }
}


const std::unordered_map<std::string, std::pair<tbb::concurrent_vector<ticker>::iterator, tbb::concurrent_vector<ticker>::iterator>> &
ticker_storage::classifying_map() const {
    ;
    return this->classifying_map_;
}

const tbb::concurrent_vector<ticker> &ticker_storage::ticker_vector() const {
    return this->ticker_vector_;
}
