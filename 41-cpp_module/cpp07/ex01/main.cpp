//
// Created by ji junhyuk on 2023/06/01.
//

#include "iter.h"
#include <iostream>

template <typename T>

void mult(T& a) {
    a *= 2;
}

struct makeDouble {
    template <typename T>
    void operator()(T& value) {
        value *= 2;
    }
};


int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    iter(arr, 5, mult<int>);
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
    makeDouble dou;
    iter(arr, 5, dou);
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}