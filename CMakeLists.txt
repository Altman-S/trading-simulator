cmake_minimum_required(VERSION 3.25)
project(trading_simulator)

set(CMAKE_CXX_STANDARD 20)

include_directories(core)
include_directories(estimator)
include_directories(helper)

add_executable(trading_simulator
        core/get_file_names.cpp
        core/holding.cpp
        core/main.cpp
        core/market.cpp
        core/portfolio.cpp
        core/read_data.cpp
        core/stock.cpp
        core/knapsack_solve.cpp
        core/header/get_file_names.h
        core/header/holding.h
        core/header/market.h
        core/header/portfolio.h
        core/header/read_data.h
        core/header/stock.h
        core/header/knapsack_solve.h
        helper/print_help.cpp
        helper/print_help.h)

add_executable(weights_estimator
        estimator/weights_estimator.cpp
        helper/print_help.cpp
        helper/print_help.h)
