//
// Created by ji junhyuk on 2023/05/23.
//

#include "Fixed.h"

int main(void)
{
    Fixed a;
    Fixed b(a);
    Fixed c;

    c = b;

    std::cout << a.getRawBits() << '\n';
    std::cout << b.getRawBits() << '\n';
    std::cout << c.getRawBits() << '\n';

    return 0;
}
