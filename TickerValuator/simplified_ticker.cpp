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

std::ostream & operator<<(std::ostream & os, const simplified_ticker &stk)  
{ 
    return os << "->" << stk.date() << " | " << stk.time() << " | " << stk.price();  
}