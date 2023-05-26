cmake_minimum_required(VERSION 3.24)
project(cpp05)

set(CMAKE_CXX_STANDARD 14)

include_directories(ex00)

add_executable(cpp05
        ex00/Bureaucrat.cpp
        ex00/Bureaucrat.h ex00/main.cpp)
