//
// Created by ji junhyuk on 2023/05/29.
//

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
    ShrubberyCreationForm form1; // 145, 137
//    AForm* form = new ShrubberyCreationForm();

    Bureaucrat A("A", 146);
    Bureaucrat B("B", 145);
    Bureaucrat C("C", 130);
    A.executeForm(form1);
    A.signForm(form1);
    B.signForm(form1);
    C.signForm(form1);
    C.executeForm(form1);
    std::cout << "==========" << std::endl;

    RobotomyRequestForm form2; // 72 45
    Bureaucrat D("D", 72);
    Bureaucrat E("E", 40);
    D.executeForm(form2);
    D.signForm(form2);
    D.executeForm(form2);
    E.executeForm(form2);
    std::cout << "==========" << std::endl;

    PresidentialPardonForm form3; // 72 45
    Bureaucrat F("F", 1);
    F.signForm(form3);
    F.executeForm(form3);
    std::cout << "==========" << std::endl;
}
