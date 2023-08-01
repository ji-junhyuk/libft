//
// Created by ji junhyuk on 2023/05/29.
//

#include "Intern.hpp"

Intern::Intern() {
    mFunctionTables[0] = "ShrubberyCreationForm";
    mFunctionTables[1] = "RobotomyRequestForm";
    mFunctionTables[2] = "PresidentialPardonForm";
}

Intern::Intern(const Intern &other) {
    for (int i = 0; i < FUNC_SIZE; ++i) {
       mFunctionTables[i] = other.mFunctionTables[i];
    }
    for (int i = 0; i < TABLE_SIZE; ++i) {
       mFp[i] = other.mFp[i];
    }
}

Intern &Intern::operator=(const Intern &other) {
    if (this != &other)
    {
        for (int i = 0; i < FUNC_SIZE; ++i) {
           mFunctionTables[i] = other.mFunctionTables[i];
        }
        for (int i = 0; i < TABLE_SIZE; ++i) {
            mFp[i] = other.mFp[i];
        }
    }
    return *this;
}

Intern::~Intern() {

}

AForm *Intern::createShruberryCreationForm(const std::string target) const {
    return new ShrubberyCreationForm(target);
}

AForm *Intern::createRobotomyRequestForm(const std::string target) const {
    return new RobotomyRequestForm(target);
}

AForm *Intern::createPresidentialPardonForm(const std::string target) const {
    return new PresidentialPardonForm(target);
}

void Intern::setHashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        this->mFp[i] = 0;
    }
    this->mFp[4] = &Intern::createShruberryCreationForm;
    this->mFp[5] = &Intern::createRobotomyRequestForm;
    this->mFp[1] = &Intern::createPresidentialPardonForm;
}

int Intern::generateHash(const char *key) {
    unsigned long hash = 5381;
    while (*key)
    {
        hash = (((hash << 5) + hash) + *key) % TABLE_SIZE;
        key++;
    }
    return hash % TABLE_SIZE;
}

const char *Intern::InvalidFunctionNameException::what(void) const throw() {
    return "Invalid function name.";
}

AForm* Intern::makeForm(const std::string formName, const std::string target) {
    setHashTable();
    if (std::find(mFunctionTables, mFunctionTables + FUNC_SIZE, formName) == mFunctionTables + FUNC_SIZE)
        throw InvalidFunctionNameException();
    const char *key = formName.c_str();
    return (this->*mFp[generateHash(key)])(target);
}