//
// Created by ji junhyuk on 2023/05/25.
//

#ifndef CPP04_CAT_H
#define CPP04_CAT_H

#include "Animal.h"

class Cat : public Animal {

public:
    Cat();
    Cat(const Cat& other);
    Cat& operator=(const Cat& other);
    ~Cat();

    void makeSound() const;
};


#endif //CPP04_CAT_H
