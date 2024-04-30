#include "CurrencyMoneyRate.h"

int main() {

    std::string myApiKey = "cur_live_WfksVADTNR3jWlyVf9EA8C44hYAXQUakueKcYKvF";

    CurrencyMoneyRate myCurrency(myApiKey);
    myCurrency.inputInfo();

    return 0;
}
