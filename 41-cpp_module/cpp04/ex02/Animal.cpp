#include "Animal.hpp"

Animal::Animal() : mType("default") {
    std::cout << "[Animal] Default constructor is called" << std::endl;
}

Animal::Animal(std::string type) : mType(type) {
    std::cout << "[Animal] Single argument constructor is called" << std::endl;
}

Animal::Animal(const Animal &other) {
    std::cout << "[Animal] Copy constructor is called" << std::endl;
    mType = other.mType;
}

Animal &Animal::operator=(const Animal &other) {
    std::cout << "[Animal] Copy constructor is called" << std::endl;
    if (this != &other) {
        mType = other.mType;
    }
    return *this;
}

Animal::~Animal() {
    std::cout << "[Animal] destructor is called" << std::endl;
}

const std::string &Animal::getType() const {
    return mType;
}
