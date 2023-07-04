#include <vector>
#include <iostream>
#include "easyfind.h"

int main(void)
{
    std::vector<int> v(5);
    for (int i = 0; i < 5; ++i) {
        v.push_back(i + 1);
    }
    std::vector<int>::iterator it = easyfind(v, 5);
    if (it != v.end()) {
        std::cout << *easyfind(v, 5) << std::endl;
    }
    else {
        std::cout << "no searched" << std::endl;
    }

    it = easyfind(v, 50);
    if (it != v.end()) {
        std::cout << *easyfind(v, 5) << std::endl;
    }
    else {
        std::cout << "no searched" << std::endl;
    }
}
