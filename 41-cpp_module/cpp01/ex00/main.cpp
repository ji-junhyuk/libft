//
// Created by Junhyuk Ji on 3/1/23.
//

#include "Zombie.hpp"

int main(void)
{
    std::cout << "====anonymous zombie()====" << '\n';
    Zombie zombie;
    zombie.announce();

    std::cout << '\n';
    if (true)
    {
        std::cout << "====junji zombie()====" << '\n';
        Zombie zombie2("junji");
        zombie2.announce();
    }
    std::cout << '\n';
    std::cout << "====jun zombie() on heap====" << '\n';
    Zombie *zombie3 = zombie.newZombie("jun");
    zombie3->announce();
    std::cout << '\n';

    std::cout << "==== juni randomchump() ====" << '\n';
    Zombie zombie4("juni");
    zombie4.randomChump("juni2");
    std::cout << '\n';

    delete zombie3; // zombie3, jun
    std::cout << '\n';
//    system("leaks ZOMBIE");
}
