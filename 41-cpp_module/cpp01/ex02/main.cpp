//
// Created by Junhyuk Ji on 3/3/23.
//

#include <iostream>
#include <string>

int main(void) {
    std::string str1 = "HI THIS IS BRAIN";
    std::string *stringPTR = &str1;
    std::string &stringREF = str1;

    std::cout << &str1 << '\n';
    std::cout << stringPTR << '\n';
    std::cout << &stringREF << '\n';

    std::cout << str1 << '\n';
    std::cout << *stringPTR << '\n';
    std::cout << stringREF << '\n';

    std::string str2 = "hello";
    stringREF = str2;
    //stringREF = &str2;
    std::cout << stringREF << '\n';
}
