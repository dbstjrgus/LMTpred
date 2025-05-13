
#include <chrono>
#include <thread>
#include "apiaccess.h"
#include "MovingAvg.h"

/**
 * The project uses alphavantage stock api, with time series of 5 minutes.
 * The premises is built around that so lets not change it advocating for too much flexibilities
 * Thanks
 */
#include <iostream>
#include "circularDeque.h"
int main() {

    //MemoryPool<data> pool(15); // memory efficiency
    MovingAvg engine(6);
    json dat = getAPIData();
    const json& TSPMOIFTHISDONTWORK = dat["Time Series (5min)"];
    std::cout << "test 1" << std::endl;
    std::vector<std::string> timestamps;
    std::cout << "test 2" << std::endl;
    for (auto it = TSPMOIFTHISDONTWORK.begin(); it != TSPMOIFTHISDONTWORK.end(); ++it) {
        timestamps.push_back(it.key());
    }
    //std::cout << timestamps[0] << std::endl;
    std::cout << "test 3" << std::endl;
    std::sort(timestamps.begin(), timestamps.end());
    std::cout << "test 3.4" << std::endl;

    if (!dat.contains("Time Series (5min)")) {
        std::cerr << "Key 'Time Series (5min)' not found in JSON.\n";
        return 1;
    }

    for (const std::string& time : timestamps) {
        try {
            std::cout << "test 4" << std::endl;
            data d = retrievePrice(time, TSPMOIFTHISDONTWORK);
            engine.add(d);

            std::cout << time
                      << " | OpenSMA: " << engine.openSMA()
                      << " | HighSMA: " << engine.highSMA()
                      << " | LowSMA: " << engine.lowSMA()
                      << " | CloseSMA: " << engine.closeSMA()
                      << " | VolumeSMA: " << engine.volumeSMA()
                      << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Skipping " << time << ": " << e.what() << std::endl;
        }
    }
    std::cout << "test 4" << std::endl;

    //data trough[engine.maxSize];
    //json SampleJSON = retrieveRaw(target);

    return 0;


}
