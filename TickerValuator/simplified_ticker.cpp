//
// Created by Paulo Chang on 1/14/18.
//

#include "simplified_ticker.h"
#include <iostream>
#include <algorithm>

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

    //unsigned int max_days[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //bool leap_year = false;

    unsigned int date = date_;

    auto year = static_cast<unsigned short>(date / 10000);
    date -= year*10000;

    auto month = static_cast<unsigned short>(date / 100);
    date -= month*100;

    unsigned int my_time = time_;

    auto hour = static_cast<unsigned short>(my_time / 100);
    my_time -= hour * 100;

    out.write("{:02d}-{:02d}-{:02d} {:02d}:{:02d} {:.2f}\n", date, month, year, hour, my_time, price_);
}