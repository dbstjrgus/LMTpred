//
// Created by Joshua Yoon on 5/4/25.
//

#include "apiaccess.h"

using json = nlohmann::json;




json returnJson(const std::string& symbol) {
    std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol="+ symbol + "&interval=5min&apikey=" + API_KEY_1;
    cpr::Response res = cpr::Get(cpr::Url{url});
    return res.text;
}
void printRawJson(const std::string& symbol) {
    //intraday time series daily
    std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol="+ symbol + "&interval=5min&apikey=" + API_KEY_1;
    cpr::Response res = cpr::Get(cpr::Url{url});

    std::cout << "HTTP Status Code: " << res.status_code << "\n";
    std::cout << "Raw JSON response:\n" << res.text << "\n";
}
json retrieveRaw(const std::string& symbol ) {
    std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol="+ target + "&interval=5min&apikey=" + API_KEY_1;
    cpr::Response res = cpr::Get(cpr::Url{url});
    return res.text;
}


data retrievePrice(const std::string& time, const json& feed) {
    std::vector<double> stuffs;
    try {
        if (!feed.contains(time)) {
            throw std::runtime_error("Requested time not found in time series data.");
        }
        json data = feed; // res.text
        const json& timeData = feed[time];
        //const json& timeSeries = data["Time Series (5min)"]; //"Time Series (5min)"

        for (const std::string& sect : sections) {
            const double price = std::stod(timeData[sect].get<std::string>()); //"Time Series (5min)"
            //delete print statement later
            std::cout << price << std::endl;
            stuffs.push_back(price);
        }
        if (!feed.contains(time)) {
            throw std::runtime_error("Requested time not found in time series data.");
        }

    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON" << std::endl;
        throw std::runtime_error("Error parsing JSON");
    }
    return {stuffs.at(0), stuffs.at(3), stuffs.at(1), stuffs.at(2), stuffs.at(4)};
}

std::string getTimeStamp() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    int roundedMinutes = 5 * std::round(localTime -> tm_min / 5.0);

    // Handle overflow (59 → 60)
    if (roundedMinutes >= 60) {
        roundedMinutes = 0;
        localTime->tm_hour += 1;
    }
    localTime->tm_min = roundedMinutes;
    localTime->tm_sec = 0;
    std::ostringstream timeStream;
    timeStream <<  std::put_time(localTime, "%H:%M:00");
    std::string timeStr = timeStream.str();
    std::cout << timeStr << std::endl;


    std::ostringstream dateStream;
    dateStream << std::put_time(localTime, "%Y-%m-%d");
    std::string dateStr = dateStream.str();
    std::cout << dateStr << std::endl;

    std::cout << dateStr << " " << timeStr << std::endl;
    return dateStr + " " + timeStr;
}


json getAPIData() {  // this method is just for debugging because i can't afford to make a dozen api calls every time i test
    std::ifstream file("/Users/25yoon/CLionProjects/APIEXP/sample.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open sample.json\n";
        return 0;
    }

    try {
        json data;
        file >> data;  // Load and parse JSON
        std::cout << data.dump(4) << std::endl;  // Pretty print with indentation
        return data;
    } catch (const std::exception& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
    }
    return 0;

}