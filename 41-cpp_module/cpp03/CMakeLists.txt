cmake_minimum_required(VERSION 3.24)
project(cpp03)

set(CMAKE_CXX_STANDARD 14)

include_directories(ex00)

add_executable(cpp03
        ex01/ClapTrap.cpp
        ex01/ClapTrap.h
        ex01/main.cpp ex01/ScavTrap.h ex01/ScavTrap.cpp ex01/ScavTrap.h ex01/main.cpp ex02/FragTrap.h ex02/FragTrap.cpp ex02/main.cpp ex03/ScavTrap.h ex03/FragTrap.h ex03/ClapTrap.cpp ex03/FragTrap.cpp ex03/ScavTrap.cpp ex03/DiamondTrap.h ex03/DiamondTrap.cpp ex03/main.cpp ex00/ClapTrap.cpp)
