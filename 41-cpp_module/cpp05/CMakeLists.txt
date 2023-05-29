cmake_minimum_required(VERSION 3.24)
project(cpp05)

set(CMAKE_CXX_STANDARD 14)

include_directories(cpp05)

add_executable (cpp05 ex03/Intern.h ex03/Intern.cpp ex03/main.cpp ex03/AForm.cpp ex03/Bureaucrat.cpp ex03/PresidentialPardonForm.cpp ex03/RobotomyRequestForm.cpp ex03/ShrubberyCreationForm.cpp)
