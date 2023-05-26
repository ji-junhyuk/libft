//
// Created by ji junhyuk on 2023/05/22.
//

#include "Fixed.h"

Fixed::Fixed() : mFixedPointValue() {
    std::cout << "Default constructor called" << '\n';
}

Fixed::Fixed(const Fixed &other) {
    std::cout << "Copy constructor called" << '\n';
    mFixedPointValue = other.mFixedPointValue;
}

Fixed &Fixed::operator=(const Fixed &other) {
    std::cout << "Copy assginment operator called" << '\n';
    if (this != &other)
    {
        mFixedPointValue = other.getRawBits();
    }
    return *this;
}

Fixed::~Fixed() {
    std::cout << "Destructor called" << '\n';
}

int Fixed::getRawBits(void) const {
    std::cout << "getRawBits member function called" << '\n';
    return mFixedPointValue;
}

void Fixed::setRawBits(const int value) {
    std::cout << "setRawBits member function called" << '\n';
    mFixedPointValue = value;
}
