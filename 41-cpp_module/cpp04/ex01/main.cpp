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
    const Animal* animal[4];
    for (int i = 0; i < 4; ++i) {
        if (i % 2)
        {
            animal[i] = new Dog();
        }
        else
        {
           animal[i] = new Cat();
        }
    }
    for (int i = 0; i < 4; ++i) {
        animal[i]->makeSound();
    }
    for (int i = 0; i < 4; ++i) {
        delete animal[i];
    }
}

int main(void)
{
    run_main();
//    system("leaks Brain");
    return 0;
}