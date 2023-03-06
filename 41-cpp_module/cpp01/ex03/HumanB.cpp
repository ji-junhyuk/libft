//
// Created by Junhyuk Ji on 3/3/23.
//

#include "HumanB.hpp"

HumanB::HumanB(std::string name) {
    this->name = name;
    this->weapon = NULL;
}

const Weapon &HumanB::getWeapon() const {
    return *weapon;
}

void HumanB::setWeapon(Weapon &weapon) {
    this->weapon = &weapon;
}

void HumanB::attack() {
    if (this->weapon == NULL) {
        std::cout << "무기가 없습니다." << '\n';
        return ;
    }
    std::cout << this->name << " attacks with their " << this->weapon->getType() << '\n';
}
