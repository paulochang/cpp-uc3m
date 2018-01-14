//
// Created by Paulo Chang on 1/6/18.
//

#include <numeric>
#include "ticker.h"
#include <iostream>

ticker::ticker(unsigned short d, unsigned short m, unsigned short y, unsigned short h, unsigned short min,
               unsigned short secs, float decimals, std::string symbol, double price) {
    date_ = d * 1000000u + m * 10000u + y;
    time_ = h * 100u + min;
    seconds_ = secs + decimals;
    symbol_ = std::move(symbol);
    price_.push_back(price);
}

ticker::ticker(unsigned int date, unsigned short time, double seconds, std::string symbol, double price) {
    date_ = date;
    time_ = time;
    seconds_ = seconds;
    symbol_ = symbol;
    price_.push_back(price);
}

void ticker::add_price(double price) {
    price_.push_back(price);
}

double ticker::avg_price() const {
    return std::accumulate(price_.begin(), price_.end(), 0.0) / price_.size();
}


bool ticker::operator<(const ticker &a) const {
    return (symbol_ < a.symbol_) ||
           ((symbol_ == a.symbol_) && (date_ < a.date_)) ||
           ((symbol_ == a.symbol_) && (date_ == a.date_) && (time_ < a.time_)) ||
           ((symbol_ == a.symbol_) && (date_ == a.date_) && (time_ == a.time_) && (seconds_ < seconds_));
}

bool ticker::operator==(const ticker &a) const {
    return ((symbol_ == a.symbol_) && (date_ == a.date_) && (time_ == a.time_) && (seconds_ == a.seconds_));
}

unsigned int ticker::date() const {
    return date_;
}

unsigned int ticker::time() const {
    return time_;
}

double ticker::seconds() const {
    return seconds_;
}

const std::vector<double> &ticker::price() const {
    return price_;
}

const std::string &ticker::symbol() const {
    return symbol_;
}

std::ostream &operator<<(std::ostream &os, const ticker &tk) {
    return os << tk.symbol() << " date_ : " << tk.date() << " | time_: " << tk.time() << " | seconds: " << tk.seconds()
              << " | price_: " << tk.avg_price();
}  