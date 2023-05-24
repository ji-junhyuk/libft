//
// Created by ji junhyuk on 2023/05/23.
//

#ifndef CPP02_FIXED_H
#define CPP02_FIXED_H

#include <iostream>
#include <cmath>

class Fixed {

private:
    static const int mFractionalBits = 8;
    int mFixedPointValue;

public:
    Fixed();
    Fixed(const int value);
    Fixed(const float value);
    Fixed(const Fixed& other);
    Fixed& operator=(const Fixed& other);
    ~Fixed();
    float toFloat(void) const;
    int toInt(void) const;
};
std::ostream& operator<<(std::ostream& os, const Fixed& obj);


#endif //CPP02_FIXED_H
