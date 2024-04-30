#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "cpr/cpr.h"
#include "nlohmann/json.hpp"
#include "chrono"
#include "ctime"
#include "sstream"
#include "thread"

using namespace nlohmann;

#ifndef REST_API_CURRENCYMONEYRATE_H
#define REST_API_CURRENCYMONEYRATE_H

struct Date {
    int day;
    int month;
    int year;
};

class CurrencyMoneyRate {

private:

    std::string apiKey;
    std::vector<std::tuple<std::string, std::string, float, float>> outputInfo;

    void currencyExchangeRateToTheRussianRubleForSelectedDate(const std::string& curDate, const std::string& currency, float count, bool outputConsole);
    void currencyExchangeRateToTheRussianRubleForSelectedPeriod(const std::string& startDate, const std::string& endDate, const std::string &currency, float count, bool outputConsole);
    void saveInfoToFile();

    static Date parseString(const std::string& str);

public:

    explicit CurrencyMoneyRate(const std::string& myApi);
    void inputInfo();

};


#endif
