//
// Created by Paulo Chang on 1/6/18.
//

#include "ticker_storage.h"
void ticker_storage::add_ticker(ticker myTicker) {
    ticker_set_.push_back(myTicker);
    symbol_set_.insert(myTicker.get_symbol());
}

void ticker_storage::sort_ticker() {
    std::sort(ticker_set_.begin(), ticker_set_.end());
}