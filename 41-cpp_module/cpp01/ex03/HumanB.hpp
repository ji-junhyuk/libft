//
// Created by Junhyuk Ji on 3/3/23.
//

#ifndef CPP01_HUMANB_HPP
#define CPP01_HUMANB_HPP

#include "Weapon.hpp"

class HumanB {

private:
    std::string name;
    Weapon *weapon;

public:
    const Weapon &getWeapon() const;
    void setWeapon(Weapon &weapon);
    HumanB(std::string name);
    void attack();
};


#endif //CPP01_HUMANB_HPP
