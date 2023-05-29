//
// Created by ji junhyuk on 2023/05/29.
//

#include "AForm.h"
#include "ShrubberyCreationForm.h"
#include "RobotomyRequestForm.h"
#include "PresidentialPardonForm.h"
#include "Intern.h"

int main()
{
    Intern A;

    AForm *form1;
    AForm *form2;
    AForm *form3;
    Bureaucrat B;
    form1 = A.makeForm("ShrubberyCreationForm", "1");
    form2 = A.makeForm("RobotomyRequestForm", "1");
    form3 = A.makeForm("PresidentialPardonForm", "1");

    std::cout << form1->getName() << ' ' << form1->isSigned() << ' ' << form1->getRequiredSign() << ' ' << form1->getRequiredExec() << std::endl;
    std::cout << form2->getName() << ' ' << form2->isSigned() << ' ' << form2->getRequiredSign() << ' ' << form2->getRequiredExec() << std::endl;
    std::cout << form3->getName() << ' ' << form3->isSigned() << ' ' << form3->getRequiredSign() << ' ' << form3->getRequiredExec() << std::endl;
    try {
        AForm *form4;
        form4 = A.makeForm("hello", "1");
        std::cout << form4->getName() << ' ' << form4->isSigned() << ' ' << form4->getRequiredSign() << ' ' << form4->getRequiredExec() << std::endl;
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}
