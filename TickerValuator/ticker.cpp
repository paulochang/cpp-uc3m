//
// Created by Paulo Chang on 1/6/18.
//

#include <numeric>
#include "ticker.h"

ticker::ticker(unsigned short d, unsigned short m, unsigned short y, unsigned short h, unsigned short min,
               unsigned short secs, float decimals, std::string symbol, double price) {
    date_ = d * 1000000 + m * 10000 + y;
    time_ = h * 100 + min;
    seconds_ = secs + decimals;
    symbol_ = symbol;
    price_.push_back(price);
}

ticker::ticker(int date, int time, double seconds, std::string symbol, double price) {
    date_ = date;
    time_ = time;
    seconds_ = seconds;
    symbol_ = symbol;
    price_.push_back(price);
}

void ticker::add_price(double price) {
    price_.push_back(price);
}

double ticker::get_avg_price() {
    return std::accumulate(price_.begin(), price_.end(), 0.0) / price_.size();
}


bool ticker::operator<(const ticker &a) const {
    return (symbol_< a.symbol_ || date_ < a.date_ || a.time_ < time_ ||
            seconds_ < a.seconds_);
}

int ticker::getDate_() const {
    return date_;
}

int ticker::getTime_() const {
    return time_;
}

double ticker::getSeconds_() const {
    return seconds_;
}

const std::vector<double> &ticker::getPrice_() const {
    return price_;
}

const std::string &ticker::getSymbol_() const {
    return symbol_;
}
