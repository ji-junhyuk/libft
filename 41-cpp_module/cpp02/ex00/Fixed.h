//
// Created by ji junhyuk on 2023/05/22.
//

#ifndef CPP02_FIXED_H
#define CPP02_FIXED_H

#include <iostream>

class Fixed {

private:
    int mFixedPointValue;
    static const int mFixedNumber = 8;

public:
    Fixed();
    Fixed(const Fixed& other);
    Fixed& operator=(const Fixed& other);
    ~Fixed();
    int getRawBits(void) const;
    void setRawBits(const int value);
};


#endif //CPP02_FIXED_H
