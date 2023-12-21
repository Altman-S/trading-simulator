#include "header/portfolio.h"

Portfolio::Portfolio(float initial_cash) {
    cash = initial_cash;
    cur_holdings = {};
    past_holdings = {};
}

float Portfolio::get_cur_holdings_value() {
    float sum = 0.0;
    for (auto cur_holding : cur_holdings) {
        sum += cur_holding.stock_ptr->cur_price;
    }
    return sum;
}

void Portfolio::buy(Stock *stock) {
    cash -= stock->cur_price;
    cur_holdings.emplace_back(stock);
}

void Portfolio::sell_all() {
    for (auto cur_holding : cur_holdings) {
        cur_holding.sell();
        cash += cur_holding.sell_price;
        past_holdings.push_back(cur_holding);
    }
    cur_holdings = {};
}
