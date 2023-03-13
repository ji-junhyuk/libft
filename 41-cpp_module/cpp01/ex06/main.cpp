//
// Created by Junhyuk Ji on 3/10/23.
//

#include "Harl.hpp"

void    put_error(const char *str)
{
    std::cout << str << '\n';
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        put_error("Not valid arguments.");
    Harl harl;
    std::string key(argv[1]);
   harl.Complain(key);
}
