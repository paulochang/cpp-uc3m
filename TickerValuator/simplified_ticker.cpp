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

void simplified_ticker::write(fmt::MemoryWriter &out) {

    using namespace std;

    unsigned int date = date_;
    
    unsigned short year = date/10000;
    date -= year*10000;

    unsigned short month = date/100;
    date -= month*100;

    unsigned int my_time = time_;

    unsigned short hour = my_time / 100;
    my_time -= hour * 100;

    out.write("{:02d}-{:02d}-{:02d} {:02d}:{:02d} {:.2f}\n", date, month, year, hour, my_time, price_);
}