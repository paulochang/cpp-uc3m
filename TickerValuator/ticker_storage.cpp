//
// Created by Paulo Chang on 1/6/18.
//

#include "ticker_storage.h"

struct SymbolComparer {
    bool operator()(const ticker &s, const std::string &i) {
        return s.symbol() < i;
    }

    bool operator()(const std::string &i, const ticker &s) {
        return i < s.symbol();
    }
};

void ticker_storage::add_ticker(ticker myTicker) {
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
    for (auto i : symbol_set_) {
        this->classifying_map_.insert(
                make_pair(i, std::equal_range(ticker_vector_.begin(), ticker_vector_.end(), i, SymbolComparer())));
    }
    is_classified = true;
}


const std::unordered_map<std::string, std::pair<std::vector<ticker>::iterator, std::vector<ticker>::iterator>> &
ticker_storage::classifying_map() const {
    return this->classifying_map_;
}

const std::vector<ticker> &ticker_storage::ticker_vector() const {
    return this->ticker_vector_;
}
