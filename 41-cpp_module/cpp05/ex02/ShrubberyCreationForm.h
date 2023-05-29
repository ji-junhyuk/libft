//
// Created by ji junhyuk on 2023/05/29.
//

#ifndef CPP05_SHRUBBERYCREATIONFORM_H
#define CPP05_SHRUBBERYCREATIONFORM_H


#include "Bureaucrat.h"
#include "AForm.h"
#include "fstream"

class ShrubberyCreationForm : public AForm {

private:
    std::string mTarget;

public:
    ShrubberyCreationForm();
    ShrubberyCreationForm(std::string target);
    ShrubberyCreationForm(const ShrubberyCreationForm& other);
    ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);
    virtual ~ShrubberyCreationForm();

    virtual void execute(const Bureaucrat& executor) const;
};


#endif //CPP05_SHRUBBERYCREATIONFORM_H
