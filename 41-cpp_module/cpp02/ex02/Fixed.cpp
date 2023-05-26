//
// Created by ji junhyuk on 2023/05/23.
//

#include "Fixed.h"

Fixed::Fixed() : mFixedPointValue() {
}

Fixed::Fixed(const int value) {
	mFixedPointValue = value;
    mFixedPointValue = (value << mFractionalBits);
}

Fixed::Fixed(const float value) {
    mFixedPointValue = (int)roundf(value * (1 << mFractionalBits));
}

Fixed::Fixed(const Fixed &other) {
    mFixedPointValue = other.mFixedPointValue;
}

Fixed &Fixed::operator=(const Fixed &other) {
    if (this != &other)
    {
        mFixedPointValue = other.mFixedPointValue;
    }
    return *this;
}

Fixed::~Fixed() {
}

float Fixed::toFloat(void) const {
    return (float)mFixedPointValue / (1 << mFractionalBits);
}

int Fixed::toInt(void) const {
    return mFixedPointValue >> 8;
}

bool Fixed::operator>(const Fixed &other) const {
    return mFixedPointValue > other.mFixedPointValue;
}

bool Fixed::operator<(const Fixed &other) const {
    return mFixedPointValue < other.mFixedPointValue;
}

bool Fixed::operator>=(const Fixed &other) const {
    return mFixedPointValue >= other.mFixedPointValue;
}

bool Fixed::operator<=(const Fixed &other) const {
    return mFixedPointValue <= other.mFixedPointValue;
}

bool Fixed::operator==(const Fixed &other) const {
    return mFixedPointValue == other.mFixedPointValue;
}

bool Fixed::operator!=(const Fixed &other) const {
    return mFixedPointValue != other.mFixedPointValue;
}

Fixed Fixed::operator+(const Fixed &other) const {
    Fixed temp;
    temp.mFixedPointValue = mFixedPointValue + other.mFixedPointValue;
    return temp;
}

Fixed Fixed::operator-(const Fixed &other) const {
    Fixed temp;
    temp.mFixedPointValue = mFixedPointValue - other.mFixedPointValue;
    return temp;
}

Fixed Fixed::operator*(const Fixed &other) const {
    Fixed temp;
	temp.mFixedPointValue = (float)this->mFixedPointValue * other.mFixedPointValue / (1 << mFractionalBits);
    return temp;
}

Fixed Fixed::operator/(const Fixed &other) const {
    Fixed temp;
    if (other.mFixedPointValue == 0)
    {
        std::cout << "cannot be devided by zero" << '\n';
        return 0;
    }
    temp.mFixedPointValue = mFixedPointValue * (1 << mFractionalBits) / other.mFixedPointValue;
    return temp;
}

Fixed &Fixed::operator++() {
    ++mFixedPointValue;
    return *this;
}

Fixed &Fixed::operator--() {
    --mFixedPointValue;
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed temp;
    temp.mFixedPointValue = mFixedPointValue;
    ++mFixedPointValue;
    return temp;
}

Fixed Fixed::operator--(int) {
    Fixed temp;
    temp.mFixedPointValue = mFixedPointValue;
    --mFixedPointValue;
    return temp;
}

Fixed& Fixed::min(Fixed& a, Fixed& b) {
    if (a < b)
        return a;
    return b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
    if (a < b)
        return a;
    return b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
    if (a > b)
        return a;
    return b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
    if (a > b)
        return a;
    return b;
}

std::ostream &operator<<(std::ostream &os, const Fixed &obj) {
    return os << obj.toFloat();
}
