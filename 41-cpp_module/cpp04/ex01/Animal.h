//
// Created by ji junhyuk on 2023/05/25.
//

#ifndef CPP04_ANIMAL_H
#define CPP04_ANIMAL_H

#include <string>
#include <iostream>

class Animal {

protected:
    std::string mType;

public:
    Animal();
    Animal(std::string type);
    Animal(const Animal& other);
    Animal& operator=(const Animal& other);
    virtual ~Animal();

    const std::string &getType() const;

    virtual void makeSound() const;
};


#endif //CPP04_ANIMAL_H
