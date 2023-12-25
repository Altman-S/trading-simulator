#include "header/stock.h"

Stock::Stock(int id, std::string ticker, std::vector<float> prices) {
    this->id = id;
    this->ticker = ticker;
    this->prices = prices;

    cur_price = init_price = prices[0];
    price_tmr_est = 0;

    ma_2days = ma_7days = ma_14days = ma_30days = cur_price;
}

void Stock::update(int d) {
    // Update current price
    cur_price = prices[d];

    // Update moving averages (2, 7, 14, and 30)
    float old_price;
    float new_price = cur_price;

    if (d >= 2) {
        old_price = prices[d - 2];
        ma_2days = (ma_2days * 2 - old_price + new_price) / 2;
    }
    else {
        ma_2days = (prices[0] + cur_price) / 2;
    }

    if (d >= 7) {
        old_price = prices[d - 7];
        ma_7days = (ma_7days * 7 - old_price + new_price) / 7;
    }
    else {
        ma_7days = (ma_7days * d + new_price) / (d + 1);
    }

    if (d >= 14) {
        old_price = prices[d - 14];
        ma_14days = (ma_14days * 14 - old_price + new_price) / 14;
    }
    else {
        ma_14days = (ma_14days * d + new_price) / (d + 1);
    }

    if (d >= 30) {
        old_price = prices[d - 30];
        ma_30days = (ma_30days * 30 - old_price + new_price) / 30; 
    }
    else {
        ma_30days = (ma_30days * d + new_price) / (d + 1);
    }
}
