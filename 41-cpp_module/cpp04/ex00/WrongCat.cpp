#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal("WrongCat") {
    std::cout << "[WrongCat] Default constructor is called" << std::endl;
}

WrongCat::WrongCat(const WrongCat &other) {
    std::cout << "[WrongCat] Copy constructor is called" << std::endl;
    mType = other.mType;
}

WrongCat &WrongCat::operator=(const WrongCat &other) {
    std::cout << "[WrongCat] Copy assignment constructor is called" << std::endl;
    if (this != &other) {
        mType = other.mType;
    }
    return (*this);
}

WrongCat::~WrongCat() {
    std::cout << "[WrongCat] Destructor is called" << std::endl;
}

void WrongCat::makeSound() const {
    std::cout << "[WrongCat] Meow~~~~~~~~~~" << std::endl;
}