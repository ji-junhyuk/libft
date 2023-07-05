//
// Created by ji junhyuk on 2023/05/25.
//

#ifndef CPP04_WRONGCAT_HPP
#define CPP04_WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {

public:
    WrongCat();
    WrongCat(const WrongCat& other);
    WrongCat& operator=(const WrongCat& other);
    ~WrongCat();

    void makeSound() const;
};


#endif //CPP04_WRONGCAT_HPP
