#ifndef CPP04_DOG_H
#define CPP04_DOG_H

#include "Animal.h"

class Dog : public Animal {

public:
    Dog();
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    ~Dog();

    void makeSound() const;
};


#endif //CPP04_DOG_H
