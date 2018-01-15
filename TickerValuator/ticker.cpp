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

void ticker::add_price(std::vector<double> priceVector) {
    price_.insert(price_.end(), priceVector.begin(), priceVector.end());
}

double ticker::avg_price() const {
    return std::accumulate(price_.begin(), price_.end(), 0.0) / price_.size();
}


bool ticker::operator<(const ticker &a) const {
    return (symbol_ < a.symbol_) ||
        ((symbol_ == a.symbol_) && (date_ < a.date_)) ||
        ((symbol_ == a.symbol_) && (date_ == a.date_) && (time_ < a.time_)) ||
        ((symbol_ == a.symbol_) && (date_ == a.date_) && (time_ ==  a.time_) && (seconds_ < seconds_));
}

bool ticker::operator==(const ticker &a) const {
    return ((symbol_ == a.symbol_) && (date_ == a.date_) && (time_ == a.time_) && (seconds_ == a.seconds_));
}

unsigned int ticker::date() const {
    return date_;
}

unsigned short ticker::time() const {
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

//const std::string ticker::to_string() const {
//    std::string s = "ticker {"+ getSymbol_()
//                    + " date: " + std::to_string(getDate_())
//                    + " time: " + std::to_string(getTime_())
//                    + " seconds: " + std::to_string(getSeconds_())
//                    + " price: " + std::to_string(get_avg_price())
//                    +"}";
//    return s;
//}

std::ostream & operator<<(std::ostream & os, const ticker & tk)  
{ 
    return os << tk.symbol() << ": " << tk.date() << " | " << tk.time() << tk.seconds() << " | " << tk.avg_price();  
}

std::istream & operator>>(std::istream & is, ticker & tk) {
    using namespace std;

    double price;
    std::string date_str, time_str, symbol_str;
    
    is >> date_str >> time_str >> symbol_str >> price;
    if (!is) return is;

    unsigned int date = stoi(date_str.substr(0,2) + date_str.substr(3,2) + date_str.substr(6,4));
    unsigned short time = stoi(time_str.substr(0,2) + time_str.substr(3,2));
    double seconds = stod(time_str.substr(6, 9));
    string symbol = symbol_str.substr(1, symbol_str.length()-2);

    tk = ticker{date, time, seconds, symbol, price};

    return is;
}