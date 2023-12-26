#include "header/knapsack_solve.h"

std::vector<int> knapsack_solve(int capacity, int n, std::vector<int> weights, std::vector<float> values) {
    // dp for tracking value gain
    std::vector<std::vector<float>> dp(n, std::vector<float>(capacity + 1, 0.0));
    std::vector<std::vector<bool>> items_selected(n, std::vector<bool>(capacity + 1, false));

    // Initial the first row
    if (values[0] > 0) {
        for (int j = weights[0]; j <= capacity; ++j) {
            dp[0][j] = values[0];
            items_selected[0][j] = true;
        }
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= capacity; ++j) {
            int weight = weights[i];
            float value = values[i];

            if (j < weight) continue;

            float without_current_item = dp[i - 1][j];
            float with_current_item = dp[i - 1][j - weight] + value;
            if (with_current_item > without_current_item) {
                dp[i][j] = dp[i - 1][j - weight] + value;
                // copy items_selected[0:i-1][j - weight] to items_selected[0:i-1][j]
                for (int k = 0; k < i; ++k) {
                    items_selected[k][j] = items_selected[k][j - weight];
                }
                items_selected[i][j] = true; 
            }
        }
    }

    // Generate the selected shares
    std::vector<int> res;
    for (int i = 0; i < n; ++i) {
        if (items_selected[i][capacity]) res.push_back(i);
    }
    
    return res;
}