#include <iostream>
#include <string>
#include "cpr/cpr.h"
#include "nlohmann/json.hpp"

using namespace nlohmann;

#ifndef REST_API_CURRENCYMONEYRATE_H
#define REST_API_CURRENCYMONEYRATE_H



class CurrencyMoneyRate {

private:

    std::string apiKey;
    float rubleCurrency{};

    void currencyExchangeRateToTheRussianRubleForSelectedDate(const std::string& curDate, const std::string& currency, const float count);
    void currencyExchangeRateToTheRussianRubleForSelectedPeriod(const std::string& startDate, const std::string& endDate, const std::string &currency, const float count);
    void saveInfoToFile();

public:

    explicit CurrencyMoneyRate(const std::string& myApi);
    void inputInfo();

};


#endif
