//
// Created by Paulo Chang on 1/14/18.
//

#ifndef TICKERVALUATOR_AREA_UTILS_H
#define TICKERVALUATOR_AREA_UTILS_H


#include <cmath>

namespace AreaUtils {
    inline double area(const double x1, const double x2, const double y1, const double y2) {
        double currentX1;
        double currentY1;

        double intPart2 = floor(x2);

        if (floor(x1) != intPart2) {
            double m = (y2 - y1) / (x2 - x1);
            double b = (y2 - m * x2);
            currentX1 = intPart2;
            currentY1 = m * intPart2 + b;
        } else {
            currentX1 = x1;
            currentY1 = y1;
        }

        return (x2 - currentX1) * (y2 - currentY1);
    }

    inline bool isContiguous(const double x1, const double x2) {
        return (floor(x1) == floor(x2));
    }
};


#endif //TICKERVALUATOR_AREA_UTILS_H
