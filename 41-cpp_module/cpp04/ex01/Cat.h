#ifndef CPP04_CAT_H
#define CPP04_CAT_H

#include "Animal.h"
#include "Brain.h"

class Cat : public Animal {

private:
    Brain* mBrain;
public:
    Cat();
    Cat(const Cat& other);
    Cat& operator=(const Cat& other);
    ~Cat();

    void makeSound() const;
};


#endif //CPP04_CAT_H
