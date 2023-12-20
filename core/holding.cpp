#include "header/holding.h"

Holding::Holding(Stock *s) {
    stock_ptr = s;
    buy_price = s->cur_price;
}

void Holding::sell() {
    sell_price = stock_ptr->cur_price;
}
