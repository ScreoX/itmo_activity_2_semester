#include "CurrencyMoneyRate.h"

// https://api.currencyapi.com/v3/historical?apikey=cur_live_WfksVADTNR3jWlyVf9EA8C44hYAXQUakueKcYKvF&currencies=RUB&base_currency=USD&date=2024-04-07

CurrencyMoneyRate::CurrencyMoneyRate(const std::string &myApi) {
    apiKey = myApi;
}

Date CurrencyMoneyRate::parseString(const std::string &str) {

    int day, month, year;

    day = (str[8] - '0') * 10 + (str[9] - '0');
    month = (str[5] - '0') * 10 + (str[6] - '0');
    year = (str[0] - '0') * 1000 + (str[1] - '0') * 100 + (str[2] - '0') * 10 + (str[3] - '0');

    return {day, month, year};
}

void CurrencyMoneyRate::currencyExchangeRateToTheRussianRubleForSelectedDate(const std::string &curDate, const std::string& currency, float count, bool outputConsole) {

    std::string dataLink = "https://api.currencyapi.com/v3/historical?apikey=" + apiKey + "&currencies=RUB&base_currency=" + currency + "&date=" + curDate;
    cpr::Response cprResponse = cpr::Get(cpr::Url(dataLink));

    json parsedText = json::parse(cprResponse.text);

    float value = parsedText["data"]["RUB"]["value"].get<float>() * count;

    if (outputConsole) {
        outputInfo.emplace_back(curDate, currency, count, value);
    } else {
        std::cout << currency << ' ' << count << ' ' << curDate << ' ' << value << '\n';
    }
}

void CurrencyMoneyRate::currencyExchangeRateToTheRussianRubleForSelectedPeriod(const std::string &startDate, const std::string &endDate, const std::string &currency, float count, bool outputConsole) {

    Date start_date = parseString(startDate);
    Date end_date = parseString(endDate);

    tm fromDate = {0, 0, 0, start_date.day, start_date.month - 1, start_date.year - 1900};
    tm toDate = {0, 0, 0, end_date.day, end_date.month - 1, end_date.year - 1900};

    std::chrono::system_clock::time_point startDT = std::chrono::system_clock::from_time_t(mktime(&fromDate));
    std::chrono::system_clock::time_point endDT = std::chrono::system_clock::from_time_t(mktime(&toDate));

    std::chrono::system_clock::time_point curDT = startDT;

    while (curDT <= endDT) {
        time_t current_time = std::chrono::system_clock::to_time_t(curDT);
        tm *curTime = localtime(&current_time);

        char dateBuffer[11];
        strftime(dateBuffer, 11, "%Y-%m-%d", curTime);

        std::string tempDate = dateBuffer;

        currencyExchangeRateToTheRussianRubleForSelectedDate(tempDate, currency, count, outputConsole);

        curDT += std::chrono::hours(24);
    }
}

void CurrencyMoneyRate::saveInfoToFile() {

    std::ofstream outputStream;
    outputStream.open("output.txt");

    if (outputStream.is_open())
    {
        while (!outputInfo.empty()) {
            auto [currency, curDate, count, value] = outputInfo.back();
            outputInfo.pop_back();
            outputStream << currency << ' ' << count << ' ' << curDate << ' ' << value << '\n';
        }
    }
    outputStream.close();

    std::cout << "The data was successfully read into the file" << '\n';
}

void CurrencyMoneyRate::inputInfo() {

    std::cout << "Select the number of option you want:\n"
                 "1. Send information to the console.\n"
                 "2. Save current information to a file.\n";

    bool outputConsole = false;
    int output;

    std::cin >> output;

    if (output == 2) {
        outputConsole = true;
    }

    std::cout << "Select the number of option you want:\n"
                 "1. Find the rate of currency to the Russian ruble on the selected date.\n"
                 "2. Find the exchange rate to the Russian ruble for the selected period.\n";
    float count;
    std::string date, startDate, endDate;
    std::string currency;

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            // USD 2 2024-04-26
            std::cout << "Enter currency, count of currency and date.\n";

            std::cin >> currency >> count >> date;
            currencyExchangeRateToTheRussianRubleForSelectedDate(date, currency, count, outputConsole);

            if (outputConsole) {
                saveInfoToFile();
            }

            break;
        case 2:
            // USD 2 2023-04-26 2023-05-10
            std::cout << "Enter currency, count of currency, start date and end date.\n";

            std::cin >> currency >> count >> startDate >> endDate;
            currencyExchangeRateToTheRussianRubleForSelectedPeriod(startDate, endDate, currency, count, outputConsole);

            if (outputConsole) {
                saveInfoToFile();
            }

            break;

        default:
            break;
    }
}


