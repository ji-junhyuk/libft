//
// Created by ji junhyuk on 2023/05/29.
//

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main()
{
    Intern A;

    AForm *form1 = A.makeForm("ShrubberyCreationForm", "1");
    AForm *form2 = A.makeForm("RobotomyRequestForm", "1");
    AForm *form3 = A.makeForm("PresidentialPardonForm", "1");

    std::cout << form1->getName() << ' ' << form1->isSigned() << ' ' << form1->getRequiredSign() << ' ' << form1->getRequiredExec() << std::endl;
    std::cout << form2->getName() << ' ' << form2->isSigned() << ' ' << form2->getRequiredSign() << ' ' << form2->getRequiredExec() << std::endl;
    std::cout << form3->getName() << ' ' << form3->isSigned() << ' ' << form3->getRequiredSign() << ' ' << form3->getRequiredExec() << std::endl;
    try {
        AForm *form4 = A.makeForm("hello", "1");
        std::cout << form4->getName() << ' ' << form4->isSigned() << ' ' << form4->getRequiredSign() << ' ' << form4->getRequiredExec() << std::endl;
        delete form4;
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    Bureaucrat B("B", 1);
    B.signForm(*form1);
    B.executeForm(*form1);
    delete form1;
    delete form2;
    delete form3;
}
