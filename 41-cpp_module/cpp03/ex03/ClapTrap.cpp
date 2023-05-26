//
// Created by ji junhyuk on 2023/05/24.
//

#include "ClapTrap.h"

ClapTrap::ClapTrap() : mName("DEFAULT"), mHitPoints(10), mEnergyPoints(10), mAttackDamage(0) {
    std::cout << "[ClapTrap] Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string& name) : mHitPoints(10), mEnergyPoints(10), mAttackDamage(0) {
    std::cout << "[ClapTrap] Single argument constructor called" << std::endl;
    mName = name;
}

ClapTrap::ClapTrap(const ClapTrap &other) {
    std::cout << "[ClapTrap] Copy constructor called" << std::endl;
    mName = other.mName;
    mHitPoints = other.mHitPoints;
    mAttackDamage = other.mAttackDamage;
    mEnergyPoints = other.mEnergyPoints;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other) {
    std::cout << "[ClapTrap] Copy assignment constructor called" << std::endl;
    if (this != &other)
    {
        mName = other.mName;
        mHitPoints = other.mHitPoints;
        mAttackDamage = other.mAttackDamage;
        mEnergyPoints = other.mEnergyPoints;
    }
    return *this;
}

ClapTrap::~ClapTrap() {
    std::cout << "[ClapTrap] Destructor called" << std::endl;
}

void ClapTrap::attack(const std::string &target) {
    std::cout << "[Attack]" << '\n';
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
    std::cout << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
    std::cout << "[takeDamage]" << '\n';
    std::cout << mName << " take damage " << amount << std::endl;
    if (mHitPoints > 0) {
        mHitPoints -= amount;
        if (mEnergyPoints < 0)
            mEnergyPoints = 0;
    }
    else if (mEnergyPoints <= 0)
    {
        std::cout << "not enough energy" << std::endl;
    }
    getStatus();
    std::cout << '\n' << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
    std::cout << "[beRepaired]" << '\n';
   if (mEnergyPoints > 0 && mHitPoints > 0) {
       std::cout << mName << " repaired " << amount << std::endl;
       mHitPoints += amount;
       --mEnergyPoints;
   }
   else if (mEnergyPoints <= 0)
   {
       std::cout << "not enough energy" << std::endl;
   }
    getStatus();
    std::cout << '\n' << std::endl;
}

void ClapTrap::getStatus() {
    if (mHitPoints <= 0)
    {
        std::cout << "already dead" << '\n' << std::endl;
        return ;
    }
    std::cout << "[STATUS]" << std::endl;
    std::cout << "HitPoints: " << mHitPoints << std::endl;
    std::cout << "AttackDamage: " << mAttackDamage << std::endl;
    std::cout << "EnergyPoints: " << mEnergyPoints << std::endl;
}
