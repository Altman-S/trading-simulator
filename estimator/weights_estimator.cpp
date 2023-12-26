#include <iostream>
#include <fstream>
#include <sstream>

#include <math.h>
#include <vector>
#include <string>


// Read the S&P data to calculate the weights
// 2021/10/1 - 2023/9/29, 502 working days in total
void read_data(std::vector<float> &prices) {
    std::ifstream file("SPY.csv");

    if (!file.is_open()) {
        std::cerr << "Cannot find the input data!" << std::endl;
    }

    std::string line;
    std::getline(file, line);  // ignore the first line
    float val;
    int day = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int col = 0;
        while (ss >> val) {
            if (col == 7) {
                prices[day] = val;
                ++day;
            }

            if (ss.peek() == ',') {
                ss.ignore();
            }

            ++col;
        }
    }

    file.close();
}

// Generate the moving average for current stock prices
float ma(const std::vector<float> &prices, int day, int n) {
    if (day == 0) return prices[0];

    float sum = 0.0;
    int p = std::min(day, n);
    for (int i = 0; i < p; ++i) {
        sum += prices[day - i];
    }

    return sum / p;
}

// Define the estimator function
float est(std::vector<float> &prices, int day, float w1, float w2, float w3, float w4) {
    return w1 * ma(prices, day, 2) + w2 * ma(prices, day, 7) + w3 * ma(prices, day, 14) + w4 * ma(prices, day, 30);
}

// The error between the actual price tomorrow and predicted price
float err(const std::vector<float> &prices, int i, float price_tmr_pred) {
    return std::abs(prices[i + 1] - price_tmr_pred);
}

// The error percentage for price today
float err_percent(const std::vector<float> &prices, int i, float price_tmr_pred) {
    return err(prices, i, price_tmr_pred) / prices[i];
}

// The gain
float gain(const std::vector<float> &prices, int i, float price_tmr_pred) {
    return prices[i + 1] - price_tmr_pred;
}


int main() {
    // Read the SPY data in
    const int days = 502;
    std::vector<float> prices;
    read_data(prices);

    // Define the range of weights for the estimator
    int granularity = 10;
    float start = -1;
    float mid = 0;
    float end = 1;
    float increment = end / granularity;
    std::vector<float> vals;

    vals.push_back(start);
    for (int i = 1; i < granularity; ++i) vals.push_back(start + i * increment);
    vals.push_back(mid);
    for (int i = 1; i < granularity; ++i) vals.push_back(mid + i * increment);
    vals.push_back(end);

    float err_lowest = 1e9;
    float gain_largest = 0;
    std::vector<float> weights_best(4, 0);

    for (float w1 : vals) {
        for (float w2 : vals) {
            for (float w3 : vals) {
                for (float w4 : vals) {
                    float cur_gain = 0;
                    
                    for (int i = 0; i < days - 1; ++i) {
                        float price_tmr_pred = est(prices, i, w1, w2, w3, w4);
                        // std::cout << price_tmr_pred << std::endl;
                        // std::cout << prices[i] << std::endl;
                        float ratio = price_tmr_pred / prices[i];
                        // Only accept reasonable predications, currently it's 10%
                        if (ratio < 0.9 || ratio > 1.1) {
                            break;
                        }
                        cur_gain += gain(prices, i, price_tmr_pred);
                    }

                    // Set the best weights
                    if (cur_gain > gain_largest) {
                        weights_best[0] = w1;
                        weights_best[1] = w2;
                        weights_best[2] = w3;
                        weights_best[3] = w4;
                        gain_largest = cur_gain;
                    }
                }
            }
        }
    }

    std::cout << "\n\n\n" << std::endl;
    std::cout << "Range: [" << start << ", " << end << "]" << std::endl;
    std::cout << "Granularity: " << granularity << ", Increment: " << increment << std::endl;
    std::cout << "Largest total gain: " << gain_largest << std::endl;
    std::cout << "weights:" << std::endl;
    for (float w : weights_best) {
        std::cout << w << std::endl;
    }

    return 0;
}







