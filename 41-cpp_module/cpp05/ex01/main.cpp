//
// Created by ji junhyuk on 2023/05/26.
//

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
    Bureaucrat A;

    Bureaucrat B("B", 80);

    Form form1;
    Form form2("Form2", false, 85, 85);
    Form form3("Form3", false, 50, 55);
    try {
        Form form4("Form4", false, -2, 0);
    } catch (const Form::GradeTooHighException& e) {
        std::cout << "Form4 " <<  e.what() << std::endl;
    }

    A.signForm(form1);
    B.signForm(form1);
    B.signForm(form2);
    B.signForm(form3);
    std::cout << form1 << std::endl;
    std::cout << form2 << std::endl;
    std::cout << form3 << std::endl;

    Bureaucrat C("C", 1);
    C.signForm(form1);
    C.signForm(form2);
    C.signForm(form3);
    std::cout << form1 << std::endl;
    std::cout << form2 << std::endl;
    std::cout << form3 << std::endl;
}