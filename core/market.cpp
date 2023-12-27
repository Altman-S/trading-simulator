#include "header/market.h"

Market::Market(std::vector<Stock> stocks) {
    this->size = stocks.size();
    this->stocks = stocks;
    update(0);
}

void Market::update(int day) {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        stocks.at(i).update(day);
        sum += stocks.at(i).cur_price;
    }
    value = sum;
}

void Market::predict(int day) {
    // TODO: the weights need to be estimated
    float weights[4] = {0.879, 0.255, -0.610, 0.394};
    for (int i = 0; i < size; ++i) {
        stocks.at(i).price_tmr_est = weights[0] * stocks.at(i).ma_2days + weights[1] * stocks.at(i).ma_7days
                                   + weights[2] * stocks.at(i).ma_14days + weights[3] * stocks.at(i).ma_30days;
    }
}

void Market::cheat_predict(int day) {
    for (int i = 0; i < size; ++i) {
        stocks.at(i).price_tmr_est = stocks.at(i).prices.at(day + 1);
    }
}
