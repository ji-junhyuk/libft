#include "Dog.hpp"

Dog::Dog() : Animal("Dog") {
    std::cout << "[Dog] Default constructor called" << std::endl;
}

Dog::Dog(const Dog &other) {
    std::cout << "[Dog] Copy constructor called" << std::endl;
    mType = other.mType;
}

Dog &Dog::operator=(const Dog &other) {
    std::cout << "[Dog] Copy assignment constructor called" << std::endl;
    if (this != &other) {
        mType = other.mType;
    }
    return *this;
}

Dog::~Dog() {
    std::cout << "[Dog] Destructor called" << std::endl;
}

void Dog::makeSound() const {
    std::cout << "[Dog] Bark~~~~~~~~~~" << std::endl;
}
