//
// Created by ji junhyuk on 2023/05/26.
//

#include "Bureaucrat.h"

int main(void)
{
    Bureaucrat A("A", 1);
    std::cout << A;
    try {
        A.increaseGrade();
    } catch (const Bureaucrat::GradeTooHighException& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "===========================" << '\n' << std::endl;

    Bureaucrat B("B", 150);
    std::cout << B;
    try {
        B.decreaseGrade();
    } catch (const Bureaucrat::GradeTooLowException& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "===========================" << '\n' << std::endl;

    try {
        Bureaucrat C("E", -2);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "===========================" << '\n' << std::endl;

    try {
        Bureaucrat D(Bureaucrat("A", 250));
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "===========================" << '\n' << std::endl;

    Bureaucrat E("C", 100);
    std::cout << E;
    E.increaseGrade();
    E.increaseGrade();
    E.decreaseGrade();
    std::cout << E;
    std::cout << "===========================" << '\n' << std::endl;

    Bureaucrat D(A);
    std::cout << D;
    std::cout << "===========================" << '\n' << std::endl;
}