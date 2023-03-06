//
// Created by Junhyuk Ji on 3/3/23.
//

#ifndef CPP01_HUMANA_HPP
#define CPP01_HUMANA_HPP

#include "Weapon.hpp"

class HumanA {

private:
    std::string name;
    Weapon &weapon;

public:
    HumanA(std::string name, Weapon &weapon);
    void attack();
};


#endif //CPP01_HUMANA_HPP
