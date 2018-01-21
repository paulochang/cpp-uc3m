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

    int max_days [12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char output [50];
    bool leap_year = false;

    unsigned int date = date_;
    
    unsigned short year = date/10000;
    date -= year*10000;

    unsigned short month = date/100;
    date -= month*100;

    unsigned int time = time_;

    unsigned short hour = my_time / 100;
    my_time -= hour * 100;

    if (time_ > 2359 or time_%100 > 59){
        cerr << fmt::format("Invalid value for time: {:02d}:{:02d}\n", hour, time);
    }

    if (month > 12 or date > max_days[month-1]){
        cerr << fmt::format("Invalid value for date: {:02d}-{:02d}-{:02d}\n", date, month, year);
    }

    if (month == 2){
        if (year%4 != 0){
            leap_year = false;
        } else if (year%100 != 0){
            leap_year = true;
        } else if (year%400 != 0){
            leap_year = false;
        }

        if (date == 29 and !leap_year){
            cerr << fmt::format("Invalid leap year:: {:02d}-{:02d}-{:02d}\n", date, month, year);
        }
    }
    

    out.write("{:02d}-{:02d}-{:02d} {:02d}:{:02d} {:.2f}\n", date, month, year, hour, time, price_);
}