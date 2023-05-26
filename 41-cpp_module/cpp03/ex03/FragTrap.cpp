//
// Created by ji junhyuk on 2023/05/25.
//

#include "FragTrap.h"

FragTrap::FragTrap() : ClapTrap() {
    std::cout << "[FragTrap]: Default constructor called" << std::endl;
    mHitPoints = 100;
    mEnergyPoints = 100;
    mAttackDamage = 30;
}

FragTrap::FragTrap(std::string &name) : ClapTrap(name) {
    std::cout << "[FragTrap]: Single argument constructor called" << std::endl;
    mName = name;
    mHitPoints = 100;
    mEnergyPoints = 100;
    mAttackDamage = 30;
}

FragTrap::FragTrap(const FragTrap &other) {
    std::cout << "[FragTrap]: Copy constructor called" << std::endl;
    mName = other.mName;
    mHitPoints = other.mHitPoints;
    mEnergyPoints = other.mEnergyPoints;
    mAttackDamage = other.mAttackDamage;
}

FragTrap &FragTrap::operator=(const FragTrap &other) {
    std::cout << "[FragTrap]: Copy assignment constructor called" << std::endl;
    if (this != &other)
    {
        mName = other.mName;
        mHitPoints = other.mHitPoints;
        mEnergyPoints = other.mEnergyPoints;
        mAttackDamage = other.mAttackDamage;
    }
    return (*this);
}

FragTrap::~FragTrap() {
    std::cout << "[FragTrap]: Destructor called" << std::endl;
}

void FragTrap::highFiveGuys(void) {
    std::cout << "[FragTrap]: highfiveguys~" << std::endl;
}
