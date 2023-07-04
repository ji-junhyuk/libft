cmake_minimum_required(VERSION 3.24)
project(cpp08)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpp08
         ex02/MutantStack.h ex02/MutantStack.tpp ex02/main.cpp ex00/easyfind.h ex01/Span.h)