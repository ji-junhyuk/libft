//
// Created by ji junhyuk on 2023/05/29.
//

#ifndef CPP05_PRESIDENTIALPARDONFORM_H
#define CPP05_PRESIDENTIALPARDONFORM_H


#include "AForm.h"
#include "Bureaucrat.h"

class PresidentialPardonForm : public AForm {

private:
    std::string mTarget;

public:
    PresidentialPardonForm();
    PresidentialPardonForm(std::string target);
    PresidentialPardonForm(const PresidentialPardonForm& other);
    PresidentialPardonForm& operator=(const PresidentialPardonForm& other);
    virtual ~PresidentialPardonForm();

    virtual void execute(const Bureaucrat &executor) const;
};


#endif //CPP05_PRESIDENTIALPARDONFORM_H
