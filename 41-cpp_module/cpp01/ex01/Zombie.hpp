//
// Created by Junhyuk Ji on 3/1/23.
//

#ifndef CPP01_ZOMBIE_HPP
#define CPP01_ZOMBIE_HPP

#include <iostream>

class Zombie {

private:
    std::string mName;

public:
    Zombie();
    Zombie(std::string name);
    Zombie* newZombie(std::string name);
    ~Zombie();
    void randomChump(std::string name);
    void Announce(void);
    void SetName(const std::string &mName);
};

Zombie* zombieHorde(int N, std::string name);

#endif //CPP01_ZOMBIE_HPP
