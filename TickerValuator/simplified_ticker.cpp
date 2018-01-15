//
// Created by Paulo Chang on 1/14/18.
//

#include "simplified_ticker.h"
#include <iostream>

simplified_ticker::simplified_ticker(unsigned int date, unsigned short time, double price) {
    date_ = date;
    time_ = time;
    price_ = price;
}

unsigned int simplified_ticker::date() const {
    return date_;
}

unsigned int simplified_ticker::time() const {
    return time_;
}

double simplified_ticker::price() const {
    return price_;
}

std::ostream & operator<<(std::ostream & os, const simplified_ticker &stk) {

    using namespace std;

    string date_str = to_string(stk.date());
    string time_str = to_string(stk.time());
    int date_length = date_str.length();
    int time_length = time_str.length();
    
    return os << date_str.substr(0,date_length-6) << "-" << date_str.substr(date_length-6,2) << "-" << date_str.substr(date_length-2,2) << " " << time_str.substr(0,time_length-2) << ":" << time_str.substr(time_length-2,2) << " " << stk.price();  
}