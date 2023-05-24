cmake_minimum_required(VERSION 3.24)
project(cpp03)

set(CMAKE_CXX_STANDARD 14)

include_directories(ex00)

add_executable(cpp03
        ex01/ClapTrap.cpp
        ex01/ClapTrap.h
        ex01/main.cpp ex01/ScavTrap.h ex01/ScavTrap.cpp ex01/ScavTrap.h ex01/main.cpp)
