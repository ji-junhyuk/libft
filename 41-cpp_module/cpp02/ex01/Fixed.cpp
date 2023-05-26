//
// Created by ji junhyuk on 2023/05/23.
//

#include "Fixed.h"

Fixed::Fixed() : mFixedPointValue() {
    std::cout << "Default constructor called" << '\n';
}

Fixed::Fixed(const int value) {
    std::cout << "Int constructor called" << '\n';
    mFixedPointValue = (value << mFractionalBits);
}

Fixed::Fixed(const float value) {
    std::cout << "Float constructor called" << '\n';
    mFixedPointValue = roundf(value * (1 << mFractionalBits));
}

Fixed::Fixed(const Fixed &other) {
    std::cout << "Copy constructor called" << '\n';
    mFixedPointValue = other.mFixedPointValue;
}

Fixed &Fixed::operator=(const Fixed &other) {
    std::cout << "Copy assignment operator called" << '\n';
    if (this != &other)
    {
        mFixedPointValue = other.mFixedPointValue;
    }
    return *this;
}

Fixed::~Fixed() {
    std::cout << "Destructor called" << '\n';
}

float Fixed::toFloat(void) const {
    return (float)mFixedPointValue / (1 << mFractionalBits);
}

int Fixed::toInt(void) const {
    return mFixedPointValue >> mFractionalBits;
}

std::ostream &operator<<(std::ostream &os, const Fixed &obj) {
    return os << obj.toFloat();
}
