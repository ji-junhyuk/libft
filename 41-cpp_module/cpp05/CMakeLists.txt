cmake_minimum_required(VERSION 3.24)
project(cpp05)

set(CMAKE_CXX_STANDARD 14)

include_directories(cpp05)

add_executable (cpp05 ex03/Intern.hpp ex03/Intern.cpp ex03/main.cpp ex03/AForm.cpp ex03/Bureaucrat.cpp ex03/PresidentialPardonForm.cpp ex03/RobotomyRequestForm.cpp ex03/ShrubberyCreationForm.cpp ex00/main.cpp ex00/Bureaucrat.cpp ex02/AForm.hpp ex02/AForm.cpp ex02/Bureaucrat.cpp ex02/main.cpp ex02/PresidentialPardonForm.cpp ex02/RobotomyRequestForm.cpp ex02/ShrubberyCreationForm.cpp ex01/Bureaucrat.cpp ex01/Form.cpp ex01/main.cpp)
