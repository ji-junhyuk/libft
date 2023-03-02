//
// Created by Junhyuk Ji on 3/1/23.
//

#include "Zombie.hpp"

int main(void)
{
    Zombie *zombie = NULL;
    zombie->zombieHorde(10, "hoho");
    for (int i = 0; i < 10; ++i) {
        zombie[i].Announce();
    }

//    system("leaks ZOMBIE");
}
