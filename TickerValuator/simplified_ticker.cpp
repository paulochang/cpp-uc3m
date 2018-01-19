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

    unsigned int date = stk.date();
    
    unsigned short year = date/10000;
    date -= year*10000;

    unsigned short month = date/100;
    date -= month*100;

    unsigned int time = stk.time();

    unsigned short hour = time/100;
    time -= hour*100;

    return os << to_string(date)+"-"+to_string(month)+"-"+to_string(year)+" "+to_string(hour)+":"+to_string(time)+" "+to_string(stk.price());
    
}