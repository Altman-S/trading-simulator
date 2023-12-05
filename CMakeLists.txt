cmake_minimum_required(VERSION 3.25)
project(trading_simulator)

set(CMAKE_CXX_STANDARD 14)

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
        core/header/get_file_names.h
        core/header/holding.h
        core/header/market.h
        core/header/portfolio.h
        core/header/read_data.h
        core/header/stock.h
        estimator/weights_estimator.cpp
        helper/print_help.cpp
        helper/print_help.h)
