#ifndef CPP04_WRONGANIMAL_HPP
#define CPP04_WRONGANIMAL_HPP

#include <string>
#include <iostream>

class WrongAnimal {

    protected:
        std::string mType;

    public:
        WrongAnimal();
        WrongAnimal(std::string type);
        WrongAnimal(const WrongAnimal& other);
        WrongAnimal& operator=(const WrongAnimal& other);
        virtual ~WrongAnimal();

        const std::string &getType() const;

        virtual void makeSound() const;
};


#endif //CPP04_WRONGANIMAL_HPP
