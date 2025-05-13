//
// Created by Joshua Yoon on 5/4/25.
//

#ifndef APIACCESS_H
#define APIACCESS_H

#pragma once
#include <string>
#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

const std::string API_KEY = "Y4TJWOM6JVOC58UJ"; // private api key
const std::string API_KEY_2 = "30TBS18SOW2IE1ZQ";
const std::string target = "LMT"; // lockheed martin

enum funcs {
    TIME_SERIES_INTRADAY=1,
    TIME_SERIES_DAILY,
    TIME_SERIES_WEEKLY,
    TIME_SERIES_MONTHLY
};

void printRawJson(const std::string& symbol);
double retrievePrice(const std::string& time, const std::string& section);


#endif //APIACCESS_H
