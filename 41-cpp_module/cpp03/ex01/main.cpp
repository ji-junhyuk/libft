//
// Created by ji junhyuk on 2023/05/24.
//

#include "ScavTrap.h"

int main(void) {
    ScavTrap A; // default HP100, MP50, DAM20
    A.attack("B");
    A.takeDamage(1);
    A.beRepaired(1);

    A.takeDamage(100);
    A.beRepaired(1);
    A.attack("B");

//    ScavTrap C;
//    for (int i = 0; i < 50; ++i) {
//        C.beRepaired(3);
//    }
//    C.beRepaired(10);

    A.guardGate();
    return (0);
}