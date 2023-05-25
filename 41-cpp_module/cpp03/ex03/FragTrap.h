//
// Created by ji junhyuk on 2023/05/25.
//

#ifndef CPP03_FRAGTRAP_H
#define CPP03_FRAGTRAP_H

#include "ClapTrap.h"

class FragTrap : virtual public ClapTrap {

public:
    FragTrap();
    FragTrap(std::string& name);
    FragTrap(const FragTrap& other);
    FragTrap& operator=(const FragTrap& other);
    ~FragTrap();

    void highFiveGuys(void);
};


#endif //CPP03_FRAGTRAP_H
