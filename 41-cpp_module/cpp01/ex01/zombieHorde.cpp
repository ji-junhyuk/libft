//
// Created by Junhyuk Ji on 3/2/23.
//

#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name) {
    Zombie *zombies = new Zombie[N];
    for (int i = 0; i < N; ++i) {
        zombies[i].SetName(name);
    }
    return (zombies);
}
