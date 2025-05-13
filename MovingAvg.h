//
// Created by Joshua Yoon on 5/12/25.
//

#ifndef MOVINGAVG_H
#define MOVINGAVG_H
#include "circularDeque.h"
#include "data.h"

class MovingAvg {
public:
    int maxSize;
    MovingAvg(int maxSize);
    void add(const data& data);
    double openSMA() const;
    double closeSMA() const;
    double highSMA() const;
    double lowSMA() const;
    double volumeSMA() const;


private:
    double open, close, high, low;
    int volume;
    circularDeque<data> *slide;
};

#endif //MOVINGAVG_H
