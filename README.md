# trading-simulator

## Basic components

+ data
+ portfolio
+ weights estimator
+ knapsack solution

## Overview

This project aims to generate profits by trading five different stocks throughout the year, beginning with an initial capital of $1000. It employs a dynamic programming algorithm to identify the optimal trades for each day, and the relevant data is extracted from CSV files and stored in suitable objects.


## Motivation

I have extensively studied C++ through various books and completed fundamental courses to solidify my understanding of the language. While I have successfully implemented numerous small-scale C++ programs, I recognize the importance of gaining experience in developing larger, more complex projects. To bridge this gap, I actively sought out interesting projects on platforms like GitHub to further enhance my skills.

Given my passion for the fintech industry and its potential to make a tangible impact on the economy and society, I decided to focus on a trading simulator project. This choice allows me to apply the knowledge and techniques I acquired during my university studies to a practical scenario. By immersing myself in this project, I aim to sharpen my C++ skills and gain valuable insights into the fintech industry.

I firmly believe that engaging with real-world projects, such as the trading simulator, not only strengthens my technical capabilities but also provides me with a solid foundation to pursue a career in the dynamic field of fintech.


## Trading strategy

In pursuit of simplicity, I opted to formulate a trading strategy based on moving averages (2, 7, 14, and 30 days).


## Knapsack solution for stock exchange



## Limitation

+ only one CPU, weights estimator could be very slow if the granularity is high


## Future work

+ another trading strategy
+ realtime data every day

## How to use

**1. Setup:**

+ Clone the project and navigate to the `trading-simulator` directory
+ Download basic compiler tools. Install cmake and clang using `brew install cmake clang` for macOS
+ If you use Linux or Window, you need to download these compiler tools compatible to your computer system, like `sudo apt-get install cmake gcc` for Linux

**2. Compile and Run:**

+ Create a build folder with `mkdir build` && `cd build`
+ Compile the program with `cmake ..` && `make`
+ Run the program using `./trading_simulator`, and observe the generated profit information
+ For weights estimator program:
    - `cd estimator` && `clang weights_estimator.cpp -o weights_estimator`
    - Run `./weights_estimator` to get the result
    - You can also adjust the range and granularity of weights to generate your own result

**3. Adding Stocks:**

+ All the stock data are downloaded from Yahoo Finance
+ We use the historical daily price data of SPY (10.01.2020 - 09.30.2022) to calculate the weights
+ We will do the trading for these stocks: APPL, AMD, BP, META, NVDA and TSLA
+ You can also download stock data from Yahoo Finance, and put them into `data` folder




