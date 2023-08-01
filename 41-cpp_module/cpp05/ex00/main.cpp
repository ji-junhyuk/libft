//
// Created by ji junhyuk on 2023/05/26.
//

#include "Bureaucrat.hpp"

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
        Bureaucrat C("C", -2);
        std::cout << C; // 실행 안됨
    } catch (const std::exception& e) {
        std::cout << "C " << e.what() << std::endl;
    }
    std::cout << "===========================" << '\n' << std::endl;

    try {
        Bureaucrat D(Bureaucrat("D", 151));
    } catch (const std::exception& e) {
        std::cout << "D " << e.what() << std::endl;
    }
    std::cout << "===========================" << '\n' << std::endl;

    Bureaucrat E("E", 100);
    std::cout << E;
    E.increaseGrade();
    std::cout << E;
    E.increaseGrade();
    std::cout << E;
    E.decreaseGrade();
    std::cout << E;
    std::cout << "===========================" << '\n' << std::endl;

    Bureaucrat D(A);
    std::cout << D;
    std::cout << "===========================" << '\n' << std::endl;
}