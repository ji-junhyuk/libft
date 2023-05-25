//
// Created by ji junhyuk on 2023/05/25.
//

#include "Animal.h"
#include "Cat.h"
#include "Dog.h"
#include "WrongAnimal.h"
#include "WrongCat.h"

void run_main()
{
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    i->makeSound(); //will output the cat sound!
    j->makeSound();
    meta->makeSound();

    std::cout << std::endl;
    delete meta;
    delete j;
    delete i;

    std::cout << std::endl;
    const WrongAnimal* meta2 = new WrongAnimal();
    const WrongAnimal* k = new WrongCat();
    std::cout << k->getType() << " " << std::endl;
    meta2->makeSound();

    std::cout << std::endl;
    delete meta2;
    delete k;
    std::cout << std::endl;
}

int main(void)
{
    run_main();
//    system("leaks Polymorphism");
    return 0;
}