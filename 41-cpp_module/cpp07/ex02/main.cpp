//
// Created by ji junhyuk on 2023/06/01.
//

#include <iostream>
#include <string>
#include "Array.h"

void run_main() {
    //operator()
    Array<int> arr(10);
    for (unsigned int i = 0; i < 10; ++i) {
        arr[i] = i;
    }
    // deep copy check
    Array<int> brr(arr);
    arr[5] = 10;
    std::cout << brr[5] << '\n';

    // operator=
    Array<int> crr = arr;
    for (int i = 0; i < 10; ++i) {
        crr[i] = i + 10;
    }
    for (int i = 0; i < 10; ++i) {
        std::cout << crr[i] << ' ';
    }
    std::cout << '\n';

    // string
    Array<std::string> A(10);
    for (int i = 0; i < 10; ++i) {
        A[i] = (i + 65);
    }
    for (int i = 0; i < 10; ++i) {
        std::cout << A[i] << ' ';
    }
    std::cout << '\n';

    // exception
    try {
        std::cout << arr[-1];
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    try {
        std::cout << arr[10];
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

int main(void)
{
    run_main();
//    system("leaks Array");
}
