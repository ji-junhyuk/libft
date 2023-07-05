#include "Dog.hpp"

Dog::Dog() : Animal("Dog"), mBrain(new Brain()) {
    std::cout << "[Dog] Default constructor called" << std::endl;
}

Dog::Dog(const Dog &other) : Animal("Dog"), mBrain(new Brain(*other.mBrain)){
    std::cout << "[Dog] Copy constructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &other) {
    std::cout << "[Dog] Copy assignment constructor called" << std::endl;
    if (this != &other)
    {
        mType = other.mType;
        delete mBrain;
        mBrain = new Brain(*other.mBrain); // 여기서 brain copy cons call
    }
    return *this;
}

Dog::~Dog() {
    std::cout << "[Dog] Destructor called" << std::endl;
    delete mBrain;
}

void Dog::makeSound() const {
    std::cout << "[Dog] Bark~~~~~~~~~~" << std::endl;
}
