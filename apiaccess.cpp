//
// Created by Joshua Yoon on 5/4/25.
//

#include "apiaccess.h"

using json = nlohmann::json;


// bro we gotta do something about this method


void printRawJson(const std::string& symbol) {
    //intraday time series daily
    std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol="+ symbol + "&interval=5min&apikey=" + API_KEY;
    cpr::Response res = cpr::Get(cpr::Url{url});

    std::cout << "HTTP Status Code: " << res.status_code << "\n";
    std::cout << "Raw JSON response:\n" << res.text << "\n";
}

double retrievePrice(const std::string& time, const std::string& section) {
    std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol="+ target + "&interval=5min&apikey=" + API_KEY;
    cpr::Response res = cpr::Get(cpr::Url{url});

    try {
        json data = json::parse(res.text);
        const json& timeSeries = data["Time Series (5min)"]; //"Time Series (5min)"


        double price = std::stod(data.at("Time Series (5min)")[time][section].get<std::string>()); //"Time Series (5min)"
        //delete print statement later
        std::cout << price << std::endl;

        if (!timeSeries.contains(time)) {
            throw std::runtime_error("Requested time not found in time series data.");
        }
        return price;


    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON" << std::endl;
        throw std::runtime_error("Error parsing JSON");
    }
}




