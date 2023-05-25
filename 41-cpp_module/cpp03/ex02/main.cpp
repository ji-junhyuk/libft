//
// Created by ji junhyuk on 2023/05/24.
//

#include "FragTrap.h"

int main(void) {
    FragTrap A; // default HP100, MP100, DAM20
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

    A.highFiveGuys();
    return (0);
}