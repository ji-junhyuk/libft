#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : mType("default") {
    std::cout << "[WrongAnimal] Default constructor is called" << std::endl;
}

WrongAnimal::WrongAnimal(std::string type) : mType(type) {
    std::cout << "[WrongAnimal] Single argument constructor is called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &other) {
    std::cout << "[WrongAnimal] Copy constructor is called" << std::endl;
    mType = other.mType;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &other) {
    std::cout << "[WrongAnimal] Copy assignment constructor is called" << std::endl;
    if (this != &other) {
        mType = other.mType;
    }
    return *this;
}

WrongAnimal::~WrongAnimal() {
    std::cout << "[WrongAnimal] Destructor is called" << std::endl;
}

const std::string &WrongAnimal::getType() const {
    return mType;
}

void WrongAnimal::makeSound() const {
    std::cout << "[WrongAnimal] ---------------------" << std::endl;
}
