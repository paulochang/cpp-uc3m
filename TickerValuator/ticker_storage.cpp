//
// Created by Paulo Chang on 1/6/18.
//

#include "ticker_storage.h"

struct Comp
{
    bool operator() ( const ticker& s, std::string i )
    {
        return s.getSymbol_() < i;
    }

    bool operator() ( std::string i, const ticker& s )
    {
        return i < s.getSymbol_();
    }
};

void ticker_storage::add_ticker(ticker myTicker) {
    is_sorted = false;
    ticker_vector_.push_back(myTicker);
    symbol_set_.insert(myTicker.getSymbol_());
}

void ticker_storage::sort_ticker() {
    std::sort(ticker_vector_.begin(), ticker_vector_.end());
    is_sorted = true;
}

void ticker_storage::classify() {
    if (!is_sorted) sort_ticker();
    for (auto i : symbol_set_) {
        classifying_map_.insert(make_pair(i,std::equal_range(ticker_vector_.begin(),ticker_vector_.end(),i, Comp())));
    }
    is_classified = true;
}

const std::unordered_map<std::string, std::pair<std::__wrap_iter<std::vector<ticker, std::__1::allocator<ticker>>::pointer>, std::__wrap_iter<std::vector<ticker, std::__1::allocator<ticker>>::pointer>>> &
ticker_storage::getClassifying_map_() const {
    return classifying_map_;
}

const std::vector<ticker> &ticker_storage::getTicker_vector_() const {
    return ticker_vector_;
}
