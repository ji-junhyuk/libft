//
// Created by ji junhyuk on 2023/05/25.
//

#ifndef CPP03_DIAMONDTRAP_H
#define CPP03_DIAMONDTRAP_H

#include "FragTrap.h"
#include "ScavTrap.h"

class DiamondTrap : public ScavTrap, public FragTrap {

private:
    std::string mName;

public:
    DiamondTrap();
    DiamondTrap(std::string &name);
    DiamondTrap(const DiamondTrap& other);
    DiamondTrap& operator=(const DiamondTrap& other);
    ~DiamondTrap();

    void whoAmI();
};


#endif //CPP03_DIAMONDTRAP_H
