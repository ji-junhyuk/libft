//
// Created by Junhyuk Ji on 7/8/23.
//

#include "RPN.hpp"

void calculate(const char* argv) {
    std::stack<int> Stack;
    std::string str = argv;
    try {
        for (int i = 0; i < static_cast<int>(str.length()); ++i) {
            if (isspace(str[i]))
                continue;
            if (!(isNum(str[i]) || isOperator(str[i]))) {
                throw InvalidFormatException();
            }
            if (isNum(str[i]))
                Stack.push(str[i] - '0');
            else {
                if (Stack.size() < 2)
                    throw InvalidFormatException();
                int right = Stack.top();
                Stack.pop();
                int left = Stack.top();
                Stack.pop();
                switch (str[i]) {
                    case '+':
                        Stack.push(left + right);
                        break;
                    case '-':
                        Stack.push(left - right);
                        break;
                    case '*':
                        Stack.push(left * right);
                        break;
                    case '/':
                        if (right == 0)
                            throw InvalidFormatException();
                        Stack.push(left / right);
                        break;
                }
            }
        }
        if (Stack.size() == 1)
            std::cout << Stack.top() << std::endl;
        else
            throw InvalidFormatException();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isNum(char c) {
    return (c >= '0' && c <= '9');
}

const char *InvalidFormatException::what() const throw() {
    return "Error";
}
