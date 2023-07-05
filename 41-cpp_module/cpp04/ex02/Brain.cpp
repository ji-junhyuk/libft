#include "Brain.hpp"

Brain::Brain() : mIdeas() {
    std::cout << "[Brain] Default constructor called" << std::endl;

}

Brain::Brain(const Brain &other) {
    std::cout << "[Brain] Copy constructor called" << std::endl;
    for (int i = 0; i < 100; ++i) {
        mIdeas[i] = other.mIdeas[i];
    }
}

Brain &Brain::operator=(const Brain &other) {
    std::cout << "[Brain] Copy constructor called" << std::endl;
    if (this != &other) {
        for (int i = 0; i < 100; ++i) {
            mIdeas[i] = other.mIdeas[i];
        }
    }
    return *this;
}

Brain::~Brain() {
    std::cout << "[Brain] destructor called" << std::endl;
}
