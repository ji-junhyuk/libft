//
// Created by Junhyuk Ji on 3/9/23.
//

#include "Harl.hpp"

int main(void)
{
    Harl harl;

    harl.Complain("DEBUG");
    std::cout << "====\n";
    harl.Complain("INFO");
    std::cout << "====\n";
    harl.Complain("WARNING");
    std::cout << "====\n";
    harl.Complain("ERROR");
    std::cout << "====\n";
    harl.Complain("errorsdfs");
}