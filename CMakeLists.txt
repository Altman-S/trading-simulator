cmake_minimum_required(VERSION 3.25)
project(trading_simulator)

set(CMAKE_CXX_STANDARD 14)

include_directories(core)
include_directories(estimator)
include_directories(helper)

add_executable(trading_simulator
        core/get_file_names.cpp
        core/get_file_names.h
        core/holding.cpp
        core/holding.h
        core/main.cpp
        core/market.cpp
        core/market.h
        core/portfolio.cpp
        core/portfolio.h
        core/read_data.cpp
        core/read_data.h
        core/stock.cpp
        core/stock.h
        estimator/weights_estimator.cpp
        helper/print_help.cpp
        helper/print_help.h)
