//
// Created by Junhyuk Ji on 3/3/23.
//

#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

int main(void) {
        Weapon club = Weapon("crude spiked club");
        HumanA bob("Bob", club);

        bob.attack();
        club.setType("mongdoonge");
        bob.attack();

        Weapon club2 = Weapon("crude spiked club2");
        HumanB jim("Jim");
        jim.attack();
        jim.setWeapon(club2);
        jim.attack();
        club2.setType("some other type of club");
        jim.attack();
        return 0;
}
