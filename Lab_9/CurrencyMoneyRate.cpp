#include "CurrencyMoneyRate.h"

// https://api.currencyapi.com/v3/historical?apikey=cur_live_WfksVADTNR3jWlyVf9EA8C44hYAXQUakueKcYKvF&currencies=RUB&base_currency=USD&date=2024-04-07

CurrencyMoneyRate::CurrencyMoneyRate(const std::string &myApi) {
    apiKey = myApi;
}

void CurrencyMoneyRate::currencyExchangeRateToTheRussianRubleForSelectedDate(const std::string &curDate) {}

void CurrencyMoneyRate::currencyExchangeRateToTheRussianRubleForSelectedPeriod(const std::string &startDate, const std::string &endDate) {

}

void CurrencyMoneyRate::saveInfoToFile() {

}

