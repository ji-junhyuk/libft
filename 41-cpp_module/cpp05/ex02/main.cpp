//
// Created by ji junhyuk on 2023/05/29.
//

#include "AForm.h"
#include "ShrubberyCreationForm.h"
#include "RobotomyRequestForm.h"
#include "PresidentialPardonForm.h"

int main()
{
    ShrubberyCreationForm form1; // 145, 137

    Bureaucrat A("A", 145);
    Bureaucrat B("B", 130);
    A.executeForm(form1);
    A.signForm(form1);
    A.executeForm(form1);
    B.executeForm(form1);

    RobotomyRequestForm form2; // 72 45
    Bureaucrat C("C", 72);
    Bureaucrat D("C", 40);
    C.executeForm(form2);
    C.signForm(form2);
    C.executeForm(form2);
    D.executeForm(form2);

    PresidentialPardonForm form3; // 72 45
    Bureaucrat E("E", 1);
    E.signForm(form3);
    E.executeForm(form3);
}
