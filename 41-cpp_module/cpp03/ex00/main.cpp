//
// Created by ji junhyuk on 2023/05/24.
//

#include "ClapTrap.h"

int main(void) {
    ClapTrap A;
    A.attack("B");
    A.takeDamage(1);
    A.beRepaired(1);

    A.takeDamage(10);
    A.beRepaired(1);
    A.attack("B");

    ClapTrap C;
    for (int i = 0; i < 10; ++i) {
        C.beRepaired(3);
    }
    C.beRepaired(10);
}