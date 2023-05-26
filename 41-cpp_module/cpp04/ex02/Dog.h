//
// Created by ji junhyuk on 2023/05/25.
//

#ifndef CPP04_DOG_H
#define CPP04_DOG_H

#include "Animal.h"
#include "Brain.h"

class Dog : public Animal {

private:
    Brain* mBrain;

public:
    Dog();
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    ~Dog();

    void makeSound() const;
};


#endif //CPP04_DOG_H
