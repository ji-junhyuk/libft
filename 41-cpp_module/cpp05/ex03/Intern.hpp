//
// Created by ji junhyuk on 2023/05/29.
//

#ifndef CPP05_INTERN_HPP
#define CPP05_INTERN_HPP


#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#define TABLE_SIZE 8
#define FUNC_SIZE 3

class Intern {

private:
    std::string mFunctionTables[FUNC_SIZE];
    AForm* (Intern::*mFp[TABLE_SIZE])(const std::string target) const;

public:
    Intern();
    Intern(const Intern& other);
    Intern& operator=(const Intern& other);
    ~Intern();

    AForm* makeForm(const std::string formName, const std::string target);
    AForm* createShruberryCreationForm(const std::string target) const;
    AForm* createRobotomyRequestForm(const std::string target) const;
    AForm* createPresidentialPardonForm(const std::string target) const;
    void setHashTable();
    int generateHash(const char* key);

public:
    class InvalidFunctionNameException : public std::exception {
        virtual const char *what(void) const throw();
    };
};


#endif //CPP05_INTERN_HPP
