//
// Created by ji junhyuk on 2023/05/24.
//

#include "ScavTrap.h"

ScavTrap::ScavTrap() : ClapTrap() {
    std::cout << "[ScavTrap]: Default constructor called" << std::endl;
    mHitPoints = 100;
    mEnergyPoints = 50;
    mAttackDamage = 20;
}

ScavTrap::ScavTrap(std::string &name) : ClapTrap(name) {
    std::cout << "[ScavTrap]: Single argument constructor called" << std::endl;
    mName = name;
    mHitPoints = 100;
    mEnergyPoints = 50;
    mAttackDamage = 20;
}

ScavTrap::ScavTrap(const ScavTrap &other) {
    std::cout << "[ScavTrap]: Copy constructor called" << std::endl;
    mName = other.mName;
    mHitPoints = other.mHitPoints;
    mEnergyPoints = other.mEnergyPoints;
    mAttackDamage = other.mAttackDamage;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &other) {
    std::cout << "[ScavTrap]: Copy assignment constructor called" << std::endl;
    if (this != &other)
    {
        mName = other.mName;
        mHitPoints = other.mHitPoints;
        mEnergyPoints = other.mEnergyPoints;
        mAttackDamage = other.mAttackDamage;
    }
    return (*this);
}

ScavTrap::~ScavTrap() {
    std::cout << "[ScavTrap]: Destructor called" << std::endl;
}

void ScavTrap::attack(const std::string &target) {
    std::cout << "[ScavTrap, Attack]" << '\n';
    if (mEnergyPoints > 0 && mHitPoints > 0) {
        std::cout << mName << " attacks " << target << ", causing " << mAttackDamage << " points of damage!"
                  << std::endl;
        --mEnergyPoints;
    }
    else if (mEnergyPoints <= 0)
    {
        std::cout << "not enough energy" << std::endl;
    }
    getStatus();
    std::cout << '\n' << std::endl;
}

void ScavTrap::guardGate() {
    std::cout << "[ScavTrap]: Gate Keep Mode" << '\n' << std::endl;
}

