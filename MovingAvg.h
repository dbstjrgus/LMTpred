//
// Created by Joshua Yoon on 5/12/25.
//

#ifndef MOVINGAVG_H
#define MOVINGAVG_H
#include "circularDeque.h"
#include "data.h"

/**
 * @class MovingAvg
 *
 * @brief Class that calculates the moving average of a series of numbers.
 *
 * The MovingAvg class maintains a fixed-size window of the most recent
 * numbers added to it and computes the average of the numbers in this window.
 * The size of the window is configurable upon initialization.
 *
 * If the number of values added exceeds the defined window size,
 * the oldest values are discarded to make room for new ones.
 *
 * This class is commonly used in scenarios where a sliding window average
 * is required, such as in data stream analysis, signal processing, or monitoring
 * real-time data for trends.
 */
class MovingAvg {
 /**
  * @brief Represents the maximum allowable size or capacity.
  *
  * This variable is used to define an upper limit for the size of a data structure,
  * buffer, container, or any system element where a maximum size restriction applies.
  * The value assigned to maxSize ensures that operations stay within predefined
  * constraints and prevents potential overflows or excessive resource utilization.
  */
public:
    int maxSize;
 /**
  * Calculates the moving average of a series of numbers over a fixed window size.
  *
  * This method maintains a sliding window of the specified size and computes
  * the average of the numbers within the window each time it is called with a new value.
  *
  * @param value The latest number to be added to the moving average calculation.
  * @return The current moving average after adding the new number to the window.
  */
 MovingAvg(int maxSize);

 /**
  * Adds two integer numbers and returns their sum.
  *
  * @param a The first integer to be added.
  * @param b The second integer to be added.
  * @return The sum of the two integers.
  */
 void add(const data& data);

 /**
  * Opens the specified SMA (shape memory alloy) actuator device, establishing
  * a connection or access point for communication and control.
  *
  * @return A boolean value indicating whether the SMA device was successfully opened.
  *         Returns true if the operation is successful, otherwise false.
  */
 double openSMA() const;

 /**
  * Closes the SMA (Simple Moving Average) calculation or operation.
  *
  * This method is used to finalize any resources or processes associated
  * with the SMA. Once called, it ensures that the SMA instance is properly
  * terminated or closed and no further operations are performed on it.
  *
  * @return True if the SMA was successfully closed; false otherwise.
  */
 double closeSMA() const;

 /**
  * Calculates and returns the Simple Moving Average (SMA) based on high values
  * within a financial time series data over a specified period.
  *
  * @return The calculated high Simple Moving Average (SMA) as a double.
  *         This value represents the average of the highest data points over
  *         the defined period in the time series.
  */
 double highSMA() const;

 /**
  * Calculates the Simple Moving Average (SMA) for a given dataset using a low period window.
  *
  * This method computes the average of the specified number of data points
  * in the dataset, which allows for the smoothing of fluctuations in the data.
  *
  * @return The calculated low period Simple Moving Average (SMA).
  */
 double lowSMA() const;

 /**
  * Calculates the Simple Moving Average (SMA) of the volume over a specified period.
  *
  * The Simple Moving Average is a commonly used statistical measure to analyze
  * data points by creating a series of averages of different subsets of the dataset.
  * This method computes the average of the volume data over a given range and
  * returns the resulting SMA value.
  *
  * @return The Simple Moving Average (SMA) of the volume as a floating-point value.
  */
 double volumeSMA() const;


 /**
  * @brief Indicates or manages the state of being open or accessible.
  *
  * The variable `open` is commonly used to represent whether a particular
  * resource, file, connection, or system is currently open, active, or
  * available for interaction. It can be employed to control or check
  * contexts like file I/O, communication channels, or operational states.
  *
  * The representation and behavior of this variable can vary depending
  * on its data type or context in implementation.
  */
private:
    double open, close, high, low;
 /**
  * @brief Represents the volume of a three-dimensional object or space.
  *
  * The variable `volume` typically holds the measurement of space occupied
  * by an object, expressed in cubic units (e.g., cubic meters, cubic centimeters).
  * It is commonly derived from the dimensions of the object such as length,
  * width, and height, or calculated through formulas specific to the shape.
  *
  * Note that the exact usage and the unit of measurement for `volume`
  * should be clarified in the related code implementation or context.
  */
 int volume;
 /**
  * @brief Represents an individual slide in a presentation or slideshow.
  *
  * This variable is used to manage and interact with a single slide entity, which may include
  * content such as text, images, and media. It can be part of a collection of slides within
  * a presentation.
  *
  * @details The slide variable typically contains attributes or references related to the content
  * and functionality of a specific slide, including layout, design elements, and associated
  * metadata. It can be utilized in operations like rendering, navigation, or updates within
  * a slideshow application or system.
  */
 circularDeque<data> *slide;
};

#endif //MOVINGAVG_H
