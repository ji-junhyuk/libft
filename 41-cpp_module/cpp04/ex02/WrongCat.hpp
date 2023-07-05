#ifndef CPP04_WRONGCAT_H
#define CPP04_WRONGCAT_H

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {

public:
    WrongCat();
    WrongCat(const WrongCat& other);
    WrongCat& operator=(const WrongCat& other);
    ~WrongCat();

    void makeSound() const;
};


#endif //CPP04_WRONGCAT_H
