//
// Created by Joshua Yoon on 5/12/25.
//

#ifndef DATA_H
#define DATA_H

struct data {
    double open, close, high, low, volume;
    data() : open(0), close(0), high(0), low(0), volume(0) {}
    data(double open, double close, double high, double low, double volume) : open(open), close(close), high(high), low(low), volume(volume) {};
};
#endif //DATA_H
