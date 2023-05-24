//
// Created by ji junhyuk on 2023/05/24.
//

#ifndef CPP03_CLAPTRAP_H
#define CPP03_CLAPTRAP_H

#include <string>
#include <iostream>

class ClapTrap {

private:
    std::string mName;
    int mHitPoints;
    int mEnergyPoints;
    int mAttackDamage;

public:
    ClapTrap();
    ClapTrap(std::string& name);
    ClapTrap(const ClapTrap& other);
    ClapTrap& operator=(const ClapTrap& other);
    ~ClapTrap();

    void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);

    void getStatus();
};

#endif //CPP03_CLAPTRAP_H
