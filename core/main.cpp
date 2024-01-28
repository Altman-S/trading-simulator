#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "header/stock.h"
#include "header/market.h"
#include "header/holding.h"
#include "header/portfolio.h"
#include "header/get_file_names.h"
#include "header/read_data.h"
#include "header/knapsack_solve.h"


int main() {
    std::cout << "trading simulator" << std::endl;

    // Initialise the days and cash parameter
    const int days = 251;
    const float initial_cash = 2000;

    // Initialise the market and portfolio
    Market market(read_data(days));
    Portfolio portfolio(initial_cash);

    // Trading simulator main code
    int day = 1;
    market.update(day);
    ++day;
    while (day < days - 2) {
        // Update stock price and moving averages for current day
        market.update(day);
        
        // Predict the stock price for tomorrow (using the trading strategy)
        market.predict(day);

        // Sell all current holdings to get the cash today
        portfolio.sell_all();

        // We use the `knapsack` algorithm to solve the stock buying and selling problem.
        // So, the main part is how to model this problem.
        // Knapsack problem has 3 main parts: capacity, weight and value
        // capacity: the cash in portfolio (we can use it to buy different stocks)
        // weight: the price for each stock
        // value: the gain for each stock

        // Initialise the capacity (to be simple, we just round down it)
        int capacity = (int) std::floor(portfolio.cash);

        // num_shares: total number of shares for all the stocks
        // max_shares: track the max_number of shares for each stock
        int market_size = market.size;
        int total_shares = 0;
        std::vector<int> max_shares(market_size, 0);
        for (int i = 0; i < market_size; ++i) {
            Stock *s_p = &(market.stocks.at(i));

            int s_id = s_p->id;
            max_shares[s_id] = (int) std::ceil(capacity / (s_p->cur_price));
            total_shares += max_shares[s_id];
        }

        // Initialise the weight and value
        std::vector<int> weight;
        std::vector<float> value;
        std::vector<int> stock_ids;
        int idx = 0;

        for (int i = 0; i < market_size; ++i) {
            Stock *s_p = &(market.stocks.at(i));

            float price = s_p->cur_price;
            float price_tmr = s_p->price_tmr_est;
            float gain_predicted = price_tmr - price;

            int s_id = s_p->id;
            for (int j = 0; j < max_shares[s_id]; ++j) {
                weight[idx] = (int) std::ceil(price);
                value[idx] = gain_predicted;
                stock_ids[idx] = s_id;
                ++idx;
            }
        }

        // Apply the knapsack algorithm to this problem
        std::vector<int> shares_selected = knapsack_solve(capacity, total_shares, weight, value);

        // Buy all the selected shares
        for (int cur_share : shares_selected) {
            int s_id = stock_ids[cur_share];
            Stock *s_p = &(market.stocks.at(s_id));
            portfolio.buy(s_p);
        }

        ++day;
    }

    // For the last day, sell all the holdings and then check the performance
    ++day;
    market.update(day);
    portfolio.sell_all();

    float total_gain = portfolio.cash - initial_cash;
    float gain_percent = (total_gain / initial_cash) * 100;

    std::cout << "Initial cash is $"  << initial_cash << std::endl;
    std::cout << "Final cash is $" << portfolio.cash << std::endl;
    std::cout << "The gain is $" << total_gain << ", achieve " << gain_percent << "\% gain" << std::endl; 

    return 0;
}
