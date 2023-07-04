cmake_minimum_required(VERSION 3.24)
project(cpp07)

set(CMAKE_CXX_STANDARD 14)

include_directories(ex00)

add_executable(cpp07
        ex02/main.cpp ex02/Array.h ex02/Array.tpp ex00/main.cpp ex01/main.cpp)
