#include "CurrencyMoneyRate.h"

int main() {

    std::string myApiKey = "cur_live_WfksVADTNR3jWlyVf9EA8C44hYAXQUakueKcYKvF";

    CurrencyMoneyRate myMoney(myApiKey);
    myMoney.inputInfo();

    return 0;
}
