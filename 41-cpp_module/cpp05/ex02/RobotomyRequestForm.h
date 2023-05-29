//
// Created by ji junhyuk on 2023/05/29.
//

#ifndef CPP05_ROBOTOMYREQUESTFORM_H
#define CPP05_ROBOTOMYREQUESTFORM_H


#include "AForm.h"
#include "Bureaucrat.h"

class RobotomyRequestForm : public AForm {

private:
    std::string mTarget;

public:
    RobotomyRequestForm();
    RobotomyRequestForm(std::string target);
    RobotomyRequestForm(const RobotomyRequestForm& other);
    RobotomyRequestForm& operator=(const RobotomyRequestForm& other);
    virtual ~RobotomyRequestForm();

    virtual void execute(const Bureaucrat& executor) const;
};


#endif //CPP05_ROBOTOMYREQUESTFORM_H
