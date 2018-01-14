//
// Created by Paulo Chang on 1/14/18.
//

#ifndef TICKERVALUATOR_SIMPLIFIED_TICKER_H
#define TICKERVALUATOR_SIMPLIFIED_TICKER_H


class simplified_ticker {
public:
    simplified_ticker(unsigned int date_, unsigned short time_, double price);

private:
    unsigned int date_;
    unsigned short time_;
    double price_;
};


#endif //TICKERVALUATOR_SIMPLIFIED_TICKER_H
