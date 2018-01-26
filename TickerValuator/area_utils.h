//
// Created by Paulo Chang on 1/14/18.
//

#ifndef TICKERVALUATOR_AREA_UTILS_H
#define TICKERVALUATOR_AREA_UTILS_H


#include <cmath>

namespace AreaUtils {
    inline double left_area(const double x1, const double x2, const double y1, const double y2) {
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

        return (x2 - currentX1) * (currentY1 + y2) / 2;
    }

    inline double right_area(const double x1, const double x2, const double y1, const double y2) {
        double currentX2;
        double currentY2;

        double intPart1 = floor(x1);
        double intPart2 = floor(x2);

        if (intPart1 != intPart2) {
            double m = (y2 - y1) / (x2 - x1);
            double b = (y2 - m * x2);
            currentX2 = intPart1 + 1;
            currentY2 = m * (intPart1 + 1) + b;
        } else {
            currentX2 = x2;
            currentY2 = y2;
        }

        return (currentX2 - x1) * (y1 + currentY2) / 2;
    }

    inline bool isContiguous(const ticker t1, const ticker t2) {
        return (t1.date() == t2.date()) && (t1.time() == t2.time()) && (floor(t1.seconds()) == floor(t2.seconds()));
    }
};


#endif //TICKERVALUATOR_AREA_UTILS_H
