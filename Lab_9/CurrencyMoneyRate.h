#include <iostream>
#include <string>

#ifndef REST_API_CURRENCYMONEYRATE_H
#define REST_API_CURRENCYMONEYRATE_H



class CurrencyMoneyRate {

private:

    std::string apiKey;
    float rubleCurrency{};

    void currencyExchangeRateToTheRussianRubleForSelectedDate(const std::string& curDate);
    void currencyExchangeRateToTheRussianRubleForSelectedPeriod(const std::string& startDate, const std::string& endDate);
    void saveInfoToFile();

public:

    explicit CurrencyMoneyRate(const std::string& myApi);

};


#endif
