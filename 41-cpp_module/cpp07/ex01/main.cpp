#include "iter.h"
#include <vector>
#include <iostream>

template <typename T>
void print(T& a) {
    std::cout << a << ' ';
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    iter(arr, 5, print<int>);
    std::cout << std::endl;

    std::string arr2[] = {"1a", "2b", "3c", "4d", "5e"};
    iter(arr2, 5, print<std::string>);
    std::cout << std::endl;

    std::vector<int>V(5);
    for (int i = 0; i < 5; ++i) {
        V[i] = i + 1;
    }
    iter(V.data(), V.size(), print<int>);
}