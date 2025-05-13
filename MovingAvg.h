//
// Created by Joshua Yoon on 5/12/25.
//

#ifndef MOVINGAVG_H
#define MOVINGAVG_H
#include "circularDeque.h"
class MovingAvg {
public:
    struct data {
        double open, close, high, low, volume;
        data() : open(0), close(0), high(0), low(0), volume(0) {}
        data(double open, double close, double high, double low, double volume) : open(open), close(close), high(high), low(low), volume(volume) {};
    };
    MovingAvg(int maxSize);
    void add(const data& data);
    double openSMA() const;
    double closeSMA() const;
    double highSMA() const;
    double lowSMA() const;
    double volumeSMA() const;

private:
    double open, close, high, low;
    int volume, maxSize;
    circularDeque<data> *slide;
};

#endif //MOVINGAVG_H
