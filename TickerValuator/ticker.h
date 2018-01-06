//
// Created by Paulo Chang on 1/6/18.
//

#ifndef TICKERVALUATOR_TICKER_H
#define TICKERVALUATOR_TICKER_H

#include <string>
#include <vector>

class ticker {
public:
    ticker(unsigned short d, unsigned short m, unsigned short y, unsigned short h, unsigned short min,
           unsigned short secs, float decimals, std::string symbol, double price);
    ticker (int date, int time, double seconds, std::string symbol, double price);
    void add_price(double price);
private:
    int date_ { 010101 };
    int time_ { 0000 };
    double seconds_{ 0.000000 };
    std::string symbol_{ ""s };
    std::vector<double> price_ { 0.00 };
};

#endif //TICKERVALUATOR_TICKER_H
