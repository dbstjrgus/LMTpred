//
// Created by Joshua Yoon on 5/12/25.
//
#include "MovingAvg.h"

MovingAvg::MovingAvg(int maxSize) {
    this-> maxSize = maxSize;
    this -> open = 0;
    this -> close = 0;
    this -> high = 0;
    this -> low = 0;
    this -> volume = 0;
    this -> slide =  new circularDeque<data>(maxSize);
}

void MovingAvg::add(const data& data) {
    if (slide->size == maxSize) {
        const MovingAvg::data& out = slide->getFront();
        open -= out.open;
        close -= out.close;
        high -= out.high;
        volume -= out.volume;
        low -= out.low;
    }
    slide->insertBack(data);
    open += data.open;
    close += data.close;
    high += data.high;
    volume += data.volume;
    low += data.low;
}

double MovingAvg::closeSMA() const {return close / slide->size; }
double MovingAvg::openSMA() const {return open / slide->size; }
double MovingAvg::volumeSMA() const {return volume / slide->size; }
double MovingAvg::highSMA() const {return high / slide->size; }
double MovingAvg::lowSMA() const {return low / slide->size; }

