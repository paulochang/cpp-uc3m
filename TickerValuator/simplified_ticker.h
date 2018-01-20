//
// Created by Paulo Chang on 1/14/18.
//

#ifndef TICKERVALUATOR_SIMPLIFIED_TICKER_H
#define TICKERVALUATOR_SIMPLIFIED_TICKER_H

#include <string>
#include "fmt/format.h"


class simplified_ticker {
public:

    simplified_ticker(unsigned int date_, unsigned short time_, double price);

    unsigned int date() const;

    unsigned int time() const;

    double price() const;

    void write(fmt::MemoryWriter &out);

private:
    unsigned int date_;
    unsigned short time_;
    double price_;
};

#endif //TICKERVALUATOR_SIMPLIFIED_TICKER_H
