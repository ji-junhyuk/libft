#include "Data.h"
#include "Serialize.h"
#include <iostream>

int main(void) {
    Data data;
    uintptr_t A;
    Data *D;

    A = Serialize::serialize(&data);
    D = Serialize::deserialize(A);

    std::cout << &data << std::endl;
    std::cout << D << std::endl;
    std::cout << D->getInt() << std::endl;
    std::cout << D->getName() << std::endl;
}

