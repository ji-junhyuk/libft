#include "Cat.hpp"

Cat::Cat() : Animal("Cat"), mBrain(new Brain) {
    std::cout << "[Cat] Default constructor called" << std::endl;
}

Cat::Cat(const Cat &other) : Animal("Cat"), mBrain(new Brain(*other.mBrain)) {
    std::cout << "[Cat] Copy constructor called" << std::endl;
}

Cat &Cat::operator=(const Cat &other) {
    std::cout << "[Cat] Copy assignment constructor called" << std::endl;
    if (this != &other) {
        mType = other.mType;
        delete mBrain;
        mBrain = new Brain(*other.mBrain);
    }
    return *this;
}

Cat::~Cat() {
    std::cout << "[Cat] Destructor called" << std::endl;
    delete mBrain;
}

void Cat::makeSound() const {
    std::cout << "[Cat] Meow~~~~~~~~~~" << std::endl;
}
