//
// Created by Paulo Chang on 1/6/18.
//

#include "ticker.h"
#include <numeric>
#include <iostream>
#include <algorithm>

ticker::ticker(const unsigned short d, const unsigned short m, const unsigned short y, const unsigned short h,
               const unsigned short min,
               const unsigned short secs, const float decimals, const std::string symbol, const double price) {
    date_ = d + m * 100u + y * 10000u;
    time_ = static_cast<unsigned short>(h * 100u + min);
    seconds_ = secs + decimals;
    symbol_ = symbol;
    price_.push_back(price);
}

ticker::ticker(const unsigned int date, const unsigned short my_time, const double seconds, const std::string symbol,
               const double price) {
    date_ = date;
    time_ = my_time;
    seconds_ = seconds;
    symbol_ = symbol;
    price_.push_back(price);
}

void ticker::add_price(const double price) {
    price_.push_back(price);
}

void ticker::add_price(const std::vector<double> priceVector) {
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

    unsigned int date = 200001001;
    unsigned short my_time = 0000;
    try {
        date = stoi(date_str.substr(6, 4) + date_str.substr(3, 2) + date_str.substr(0, 2));
        my_time = stoi(time_str.substr(0, 2) + time_str.substr(3, 2));
    } catch (const std::exception &e) {
        std::cout << e.what();
        std::cout << "date" << date_str;
        std::cout << "time" << time_str;
    }
    double seconds = stod(time_str.substr(6, 9));
    string symbol = symbol_str.substr(1, symbol_str.length()-2);

    if (seconds < 0 or seconds >= 60) {
        cerr << "Invalid value for seconds: " << seconds << endl;
        return is;
    }

    if (price < 0) {
        cerr << "Invalid value for price: " << price << endl;
        return is;
    }

    tk = ticker{date, my_time, seconds, symbol, price};

    return is;
}