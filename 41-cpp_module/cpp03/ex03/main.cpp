//
// Created by ji junhyuk on 2023/05/25.
//

#include "DiamondTrap.h"

int main(void) {
    DiamondTrap A;

    A.attack("B");
    A.takeDamage(1);
    A.beRepaired(1);

    A.takeDamage(100);
    A.beRepaired(1);
    A.attack("B");

//    FragTrap C;
//    for (int i = 0; i < 100; ++i) {
//        C.beRepaired(2);
//    }
//    C.beRepaired(9);

    A.whoAmI();
    return (0);
}