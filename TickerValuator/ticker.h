//
// Created by Paulo Chang on 1/6/18.
//

#ifndef TICKERVALUATOR_TICKER_H
#define TICKERVALUATOR_TICKER_H

#include <string>
#include <vector>

class ticker {
public:
    ticker() {}
    ticker(unsigned short d, unsigned short m, unsigned short y, unsigned short h, unsigned short min,
           unsigned short secs, float decimals, std::string symbol, double price);

    ticker(unsigned int date, unsigned short time, double seconds, std::string symbol, double price);

    void add_price(double price);

    double avg_price() const;

    bool operator<(const ticker &a) const;

    bool operator==(const ticker &a) const;

    unsigned int date() const;

    unsigned int time() const;

    double seconds() const;

    const std::vector<double> &price() const;

    const std::string &symbol() const;

private:
    //Date format is: day-month-year
    unsigned int date_{01010001};
    unsigned short time_{0000};
    double seconds_{0.000000};
    std::string symbol_{"Initial string"};
    std::vector<double> price_{};
};

std::ostream &operator<<(std::ostream &os, const ticker &tk);
std::istream &operator>>(std::istream &is, ticker & tk);

#endif //TICKERVALUATOR_TICKER_H
