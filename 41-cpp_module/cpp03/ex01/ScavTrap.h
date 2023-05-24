//
// Created by ji junhyuk on 2023/05/24.
//

#ifndef CPP03_SCAVTRAP_H
#define CPP03_SCAVTRAP_H

#include "ClapTrap.h"

class ScavTrap : public ClapTrap {

public:
    ScavTrap();
    ScavTrap(std::string& name);
    ScavTrap(const ScavTrap& other);
    ScavTrap& operator=(const ScavTrap& other);
    ~ScavTrap();

    void attack(const std::string& target);
    void guardGate();
};


#endif //CPP03_SCAVTRAP_H
