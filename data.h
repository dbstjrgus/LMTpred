//
// Created by Joshua Yoon on 5/12/25.
//

#ifndef DATA_H
#define DATA_H
#include <ostream>
struct data {
    double open, close, high, low, volume;
    data() : open(0), close(0), high(0), low(0), volume(0) {}
    data(double open, double close, double high, double low, double volume) : open(open), close(close), high(high), low(low), volume(volume) {};
};

inline std::ostream& operator<<(std::ostream& os, const data& d) {
    return os << "O:" << d.open << " C:" << d.close << " H:" << d.high << " L:" << d.low << " V:" << d.volume;
}
#endif //DATA_H
