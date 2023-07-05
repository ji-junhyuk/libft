#include "Cat.hpp"

Cat::Cat() : Animal("Cat") {
    std::cout << "[Cat] Default constructor called" << std::endl;
}

Cat::Cat(const Cat &other) {
    std::cout << "[Cat] Copy constructor called" << std::endl;
    mType = other.mType;
}

Cat &Cat::operator=(const Cat &other) {
    std::cout << "[Cat] Copy assignment constructor called" << std::endl;
    if (this != &other) {
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
