#include "CurrencyMoneyRate.h"

// https://api.currencyapi.com/v3/historical?apikey=cur_live_WfksVADTNR3jWlyVf9EA8C44hYAXQUakueKcYKvF&currencies=RUB&base_currency=USD&date=2024-04-07

CurrencyMoneyRate::CurrencyMoneyRate(const std::string &myApi) {
    apiKey = myApi;
}

void CurrencyMoneyRate::currencyExchangeRateToTheRussianRubleForSelectedDate(const std::string &curDate, const std::string& currency, const float count) {
    std::string dataLink = "https://api.currencyapi.com/v3/historical?apikey=" + apiKey + "&currencies=RUB&base_currency=" + currency + "&date=" + curDate;
    cpr::Response cprResponse = cpr::Get(cpr::Url(dataLink));

    // {"data":{"RUB":{"code":"RUB","value":92.1306318957}},"meta":{"last_updated_at":"2024-04-26T23:59:59Z"}}
    json parsedText = json::parse(cprResponse.text);

    std::cout << currency << ' ' << count << ' ' << curDate << ' ' << parsedText["data"]["RUB"]["value"].get<float>() * count;
}

void CurrencyMoneyRate::currencyExchangeRateToTheRussianRubleForSelectedPeriod(const std::string &startDate, const std::string &endDate, const std::string &currency, const float count) {

}

void CurrencyMoneyRate::saveInfoToFile() {

}

void CurrencyMoneyRate::inputInfo() {
    std::cout << "Select the number of option you want:\n"
                 "1. Find the rate of currency to the Russian ruble on the selected date.\n"
                 "2. Find the exchange rate to the Russian ruble for the selected period.\n"
                 "3. Save current information to a file.\n";

    float count;
    std::string date, startDate, endDate;
    std::string currency;

    int choice;
    std::cin >> choice;
    // USD 2 2024-04-26
    switch (choice) {
        case 1:
            std::cout << "Enter currency, count of currency and date.\n";

            std::cin >> currency >> count >> date;
            currencyExchangeRateToTheRussianRubleForSelectedDate(date, currency, count);
            break;
        case 2:
            std::cout << "Enter currency, count of currency, start date and end date.\n";

            std::cin >> currency >> count >> startDate >> endDate;
            currencyExchangeRateToTheRussianRubleForSelectedPeriod(startDate, endDate, currency, count);
            break;

        default:
            break;
    }


}

