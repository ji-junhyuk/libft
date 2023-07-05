#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

void run_main()
{
    const Animal* meta = new Animal();
    const Animal* i = new Cat();
    const Animal* j = new Dog();
    std::cout << meta->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    std::cout << j->getType() << " " << std::endl;
    meta->makeSound();
    i->makeSound();
    j->makeSound();

    std::cout << std::endl;
    delete meta;
    delete j;
    delete i;

    std::cout << std::endl;
    const WrongAnimal* meta2 = new WrongAnimal();
    const WrongAnimal* n = new WrongCat();
    std::cout << meta2->getType() << " " << std::endl;
    std::cout << n->getType() << " " << std::endl;
    meta2->makeSound();
    n->makeSound();

    std::cout << std::endl;
    delete meta2;
    delete n;
    std::cout << std::endl;
}

int main(void)
{
    run_main();
//    system("leaks Polymorphism");
    return 0;
}