//
// Created by Paulo Chang on 1/6/18.
//

#ifndef TICKERVALUATOR_TICKER_H
#define TICKERVALUATOR_TICKER_H

#include <string>

class ticker {
public:
    ticker() {}
    ticker(unsigned short d, unsigned short m, unsigned short y, unsigned short h, unsigned short min,
           unsigned short secs, float decimals, std::string symbol, double price);

    ticker(unsigned int date, unsigned short my_time, double seconds, std::string symbol, double price);

    void add_price(double price, unsigned short price_nr);

    double avg_price() const;

    bool operator<(const ticker &a) const;

    bool operator==(const ticker &a) const;

    unsigned int date() const;

    unsigned short time() const;

    double seconds() const;

    double price() const;

    unsigned short price_nr() const;

    const std::string &symbol() const;

private:
    //Date format is: day-month-year
    unsigned int date_{01010001};
    unsigned short time_{0000};
    double seconds_{0.000000};
    std::string symbol_{"Initial string"};
    double price_{0};
    unsigned short price_nr_ {0};
};

std::ostream &operator<<(std::ostream &os, const ticker &tk);
std::istream &operator>>(std::istream &is, ticker & tk);

#endif //TICKERVALUATOR_TICKER_H
