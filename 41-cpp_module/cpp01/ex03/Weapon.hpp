//
// Created by Junhyuk Ji on 3/3/23.
//

#ifndef CPP01_WEAPON_HPP
#define CPP01_WEAPON_HPP

#include <string>

class Weapon {

private:
    std::string type;

public:
    Weapon();
    Weapon weapon(std::string& type);
    const std::string &getType() const;
    void setType(const std::string &type);
};

#endif //CPP01_WEAPON_HPP
