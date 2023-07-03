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

    Bureaucrat A("A", 146);
    Bureaucrat B("B", 145);
    Bureaucrat C("C", 130);
    A.executeForm(form1);
    A.signForm(form1);
    B.signForm(form1);
    C.signForm(form1);
    C.executeForm(form1);

    RobotomyRequestForm form2; // 72 45
    Bureaucrat D("D", 72);
    Bureaucrat E("E", 40);
    D.executeForm(form2);
    D.signForm(form2);
    D.executeForm(form2);
    E.executeForm(form2);

    PresidentialPardonForm form3; // 72 45
    Bureaucrat F("F", 1);
    F.signForm(form3);
    F.executeForm(form3);
}
