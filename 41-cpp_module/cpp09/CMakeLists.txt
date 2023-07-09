cmake_minimum_required(VERSION 3.24)
project(cpp09)

set(CMAKE_CXX_STANDARD 14)

include_directories(ex00)

add_executable(cpp09
        ex00/BitcoinExchange.cpp
        ex00/BitcoinExchange.hpp
        ex00/main.cpp ex01/RPN.hpp ex01/RPN.cpp ex02/PmergeMe.hpp ex02/main.cpp ex02/PmergeMe.cpp)
