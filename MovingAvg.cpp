//
// Created by Joshua Yoon on 5/12/25.
//
#include "MovingAvg.h"


#include "MovingAvg.h"
#include <stdexcept>

/**
 * @brief Constructs a MovingAvg object with a maximum size for the sliding window.
 *
 * Initializes the moving average calculator and allocates memory for the
 * circular deque that holds the sliding window of data points.
 *
 * @param maxSize The maximum number of data points to maintain in the sliding window.
 *                This value determines the size of the circular deque.
 * @return A MovingAvg object configured with the specified maximum sliding window size.
 */
MovingAvg::MovingAvg(int maxSize)
    : maxSize(maxSize), open(0), close(0), high(0), low(0), volume(0) {
    slide = new circularDeque<data>(maxSize); // Normal dynamic allocation (no MemoryPool)
}


/**
 * @brief Adds a new data point to the sliding window and updates the aggregate values used for calculating moving averages.
 *
 * If the sliding window size exceeds the maximum size, the oldest data point is removed, and its values are subtracted
 * from the aggregate values.
 *
 * @param d The data point to add to the sliding window. It contains open, close, high, low, and volume values.
 */
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

/**
 * Computes the simple moving average (SMA) for the closing prices in the sliding window.
 *
 * @return The simple moving average of the closing prices.
 * @throws std::runtime_error if there is no data in the sliding window.
 */
double MovingAvg::closeSMA() const {
    if (slide->size == 0) throw std::runtime_error("No data");
    return close / slide->size;
}

/**
 * @brief Computes the simple moving average (SMA) of the open values.
 *
 * This method calculates the simple moving average of the "open" values
 * stored in the sliding window. If there are no data points in the
 * sliding window, an exception is thrown.
 *
 * @throws std::runtime_error if the sliding window contains no data.
 * @return The simple moving average (SMA) of the "open" values as a double.
 */
double MovingAvg::openSMA() const {
    if (slide->size == 0) throw std::runtime_error("No data");
    return open / slide->size;
}

/**
 * Calculates the simple moving average (SMA) of the volume values currently stored in the moving average window.
 *
 * @return The simple moving average (SMA) of the volume values.
 * @throws std::runtime_error If there is no data in the moving average window.
 */
double MovingAvg::volumeSMA() const {
    if (slide->size == 0) throw std::runtime_error("No data");
    return volume / slide->size;
}

/**
 * Calculates the simple moving average (SMA) for the high values of the data set.
 *
 * @return The simple moving average of the high values as a double.
 * @throws std::runtime_error If there is no data available in the sliding window.
 */
double MovingAvg::highSMA() const {
    if (slide->size == 0) throw std::runtime_error("No data");
    return high / slide->size;
}

/**
 * Computes the Simple Moving Average (SMA) for the low values of the data in the sliding window.
 *
 * This method calculates the average of the low values stored in the sliding window.
 * If the sliding window contains no data, an exception is thrown.
 *
 * @return The computed Simple Moving Average (SMA) of the low values.
 * @throws std::runtime_error if there is no data in the sliding window.
 */
double MovingAvg::lowSMA() const {
    if (slide->size == 0) throw std::runtime_error("No data");
    return low / slide->size;
}


