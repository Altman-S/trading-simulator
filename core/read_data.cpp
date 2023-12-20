#include "header/read_data.h"

std::vector<Stock> read_data(int days) {
    std::vector<Stock> stocks;
    stocks.reserve(days);

    int stock_index = 0;  // mock index for each stock

    std::vector<std::string> file_names = get_file_names();
    for (std::string file_name : file_names) {
        std::ifstream file("../data/" + file_name);

        if (!file.is_open()) {
            std::cerr << "Cannot open the file: " + file_name << std::endl;
        }

        std::string ticker = file_name.substr(0, file_name.size() - 4);  // delete .csv
        int id = stock_index;
        std::vector<float> prices;

        std::string line;
        std::getline(file, line);  // ignore the first line
        float price;  // we use the "Adj Close" column as price
        while (std::getline(file, line)) {
            std::stringstream ss(line);

            int col = 0;
            while (ss >> price) {
                if (col == 5) {
                    prices.push_back(price);
                    break;
                }

                if (ss.peek() == ',') ss.ignore();
                ++col;
            }
        }

        file.close();
        stocks.emplace_back(id, ticker, prices);
        ++stock_index;
    }

    return stocks;
}


