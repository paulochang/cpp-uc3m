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
    ticker (int date, int time, double seconds, std::string symbol, double price);
    void add_price(double price);
    double get_avg_price() const;
    bool operator<(const ticker &a) const;

    int getDate_() const;

    int getTime_() const;

    double getSeconds_() const;

    const std::vector<double> &getPrice_() const;

    const std::string &getSymbol_() const;

    const std::string to_string() const;

private:
    //Date format is: day-month-year
    int date_ { 01010001 };
    int time_ { 0000 };
    double seconds_{ 0.000000 };
    std::string symbol_ = "Initial string";
    std::vector<double> price_ { };
};

std::ostream & operator<<(std::ostream & os, const ticker & tk);
std::istream & operator>>(std::istream & is, ticker & tk);



#endif //TICKERVALUATOR_TICKER_H
