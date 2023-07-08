//
// Created by Junhyuk Ji on 7/8/23.
//

#ifndef CPP09_RPN_HPP
#define CPP09_RPN_HPP

#include <stack>
#include <string>
#include <iostream>

class InvalidFormatException : public std::exception {
public:
    const char* what() const throw();
};
bool isNum(char c);
bool isOperator(char c);
void calculate(const char *argv);

#endif //CPP09_RPN_HPP