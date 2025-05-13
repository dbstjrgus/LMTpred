//
// Created by Joshua Yoon on 5/12/25.
//
#include "MovingAvg.h"


#include "MovingAvg.h"
#include <stdexcept>

MovingAvg::MovingAvg(int maxSize)
    : maxSize(maxSize), open(0), close(0), high(0), low(0), volume(0) {
    slide = new circularDeque<data>(maxSize); // Normal dynamic allocation (no MemoryPool)
}



void MovingAvg::add(const data& d) {
    if (slide->size == maxSize) {
        const data& out = slide->getFront();
        open   -= out.open;
        close  -= out.close;
        high   -= out.high;
        volume -= out.volume;
        low    -= out.low;
    }
    slide->insertBack(d);
    open   += d.open;
    close  += d.close;
    high   += d.high;
    volume += d.volume;
    low    += d.low;
}

double MovingAvg::closeSMA() const {
    if (slide->size == 0) throw std::runtime_error("No data");
    return close / slide->size;
}

double MovingAvg::openSMA() const {
    if (slide->size == 0) throw std::runtime_error("No data");
    return open / slide->size;
}

double MovingAvg::volumeSMA() const {
    if (slide->size == 0) throw std::runtime_error("No data");
    return volume / slide->size;
}

double MovingAvg::highSMA() const {
    if (slide->size == 0) throw std::runtime_error("No data");
    return high / slide->size;
}

double MovingAvg::lowSMA() const {
    if (slide->size == 0) throw std::runtime_error("No data");
    return low / slide->size;
}


