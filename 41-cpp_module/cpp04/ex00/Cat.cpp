//
// Created by ji junhyuk on 2023/05/25.
//

#include "Cat.h"

Cat::Cat() : Animal("Cat") {
    std::cout << "[Cat] Default constructor called" << std::endl;
}

Cat::Cat(const Cat &other) {
    std::cout << "[Cat] Copy constructor called" << std::endl;
    *this = other;
}

Cat &Cat::operator=(const Cat &other) {
    std::cout << "[Cat] Copy assignment constructor called" << std::endl;
    if (this != &other)
    {
        mType = other.mType;
    }
    return *this;
}

Cat::~Cat() {
    std::cout << "[Cat] Destructor called" << std::endl;
}

void Cat::makeSound() const {
    std::cout << "[Cat] Meow~~~~~~~~~~" << std::endl;
}
