//
// Created by Junhyuk Ji on 3/3/23.
//

#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA(std::string name, Weapon &weapon) : name(name), weapon(weapon) {

}

void HumanA::attack() {
    std::cout << this->name << " attacks with their " << this->weapon.getType() << '\n';
}


