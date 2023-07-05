#ifndef CPP04_BRAIN_H
#define CPP04_BRAIN_H

#include <string>
#include <iostream>

class Brain {

private:
    std::string mIdeas[100];

public:
    Brain();
    Brain(const Brain& other);
    Brain& operator=(const Brain& other);
    ~Brain();
};


#endif //CPP04_BRAIN_H
