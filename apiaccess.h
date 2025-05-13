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
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>
#include "data.h"
#include <cstdlib>
const std::string API_KEY_1 = std::getenv("API_KEY");



const std::string target = "LMT"; // lockheed martin
const std::string sections[5] = {"1. open", "2. high", "3. low", "4. close", "5. volume"};
using json = nlohmann::json;


void printRawJson(const std::string& symbol);
data retrievePrice(const std::string& time, const json& feed);
std::string getTimeStamp();
json returnJson(const std::string& symbol);
json retrieveRaw(const std::string& symbol);
json getAPIData();



#endif //APIACCESS_H
