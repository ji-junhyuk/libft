//
// Created by Junhyuk Ji on 3/3/23.
//

#include "Weapon.hpp"

Weapon::Weapon() {

}

const std::string &Weapon::getType() const {
    return type;
}

void Weapon::setType(const std::string &type) {
    Weapon::type = type;
}
