cmake_minimum_required(VERSION 3.24)
project(cpp04)

set(CMAKE_CXX_STANDARD 14)

include_directories(ex00)

add_executable(cpp04
        ex00/Animal.cpp
        ex00/Animal.hpp
        ex00/Cat.cpp
        ex00/Cat.hpp
        ex00/Dog.cpp
        ex00/Dog.hpp
        ex00/main.cpp ex00/WrongAnimal.hpp ex00/WrongAnimal.cpp ex00/WrongCat.hpp ex00/WrongCat.cpp ex01/Animal.cpp ex01/Brain.hpp ex01/Dog.hpp ex01/Brain.cpp ex01/Cat.hpp ex01/Dog.cpp ex01/Cat.cpp ex01/main.cpp)
