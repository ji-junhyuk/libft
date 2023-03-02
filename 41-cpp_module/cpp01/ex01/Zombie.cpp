//
// Created by Junhyuk Ji on 3/1/23.
//

#include "Zombie.hpp"

Zombie::Zombie() {
    this->mName = "anonymous zombie";
}

Zombie::Zombie(std::string name) {
    this->mName = name;
}

Zombie *Zombie::newZombie(std::string name) {
    Zombie *zombie = new Zombie(name);

    return zombie;
}

void Zombie::randomChump(std::string name) {
    Zombie zombie(name);
    zombie.Announce();
}

void Zombie::Announce(void) {
    std::cout << this->mName << ": BraiiiiiiinnnzzzZ..." << '\n';
}

Zombie::~Zombie() {
    std::cout << "~Zombie(): " << this->mName << '\n';
}

void Zombie::SetName(const std::string &name) {
    Zombie::mName = name;
}