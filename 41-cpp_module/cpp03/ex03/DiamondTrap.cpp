//
// Created by ji junhyuk on 2023/05/25.
//

#include "DiamondTrap.h"

DiamondTrap::DiamondTrap() : ClapTrap(), ScavTrap(), FragTrap() {
    std::cout << "[DiamondTrap] Default constructor called" << std::endl;
    mName = "default";
    mName += "_clap_name";
    mHitPoints = 100;
    mEnergyPoints = 50;
    mAttackDamage = 20;
}

DiamondTrap::DiamondTrap(std::string &name) : ClapTrap(), ScavTrap(), FragTrap() {
    std::cout << "[DiamondTrap] One single constructor called" << std::endl;
    mName = name;
    mName += "_clap_name";
    mHitPoints = 100;
    mEnergyPoints = 50;
    mAttackDamage = 20;
}

DiamondTrap::DiamondTrap(const DiamondTrap &other) {
    std::cout << "[DiamondTrap] Copy constructor called" << std::endl;
    mName = other.mName;
    mName += "_clap_name";
    mHitPoints = other.mHitPoints;
    mEnergyPoints = other.mEnergyPoints;
    mAttackDamage = other.mAttackDamage;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &other) {
    std::cout << "[DiamondTrap] Copy assignment constructor called" << std::endl;
    if (this != &other)
    {
        mName = other.mName;
        mName += "_clap_name";
        mHitPoints = other.mHitPoints;
        mEnergyPoints = other.mEnergyPoints;
        mAttackDamage = other.mAttackDamage;
    }
    return *this;
}

DiamondTrap::~DiamondTrap() {
    std::cout << "[DiamondTrap] destructor called" << std::endl;
}

void DiamondTrap::whoAmI() {
    std::cout << "ClapTrap name : " << ClapTrap::mName << std::endl;
    std::cout << "DiamondTrap name: " << mName << std::endl;
}
