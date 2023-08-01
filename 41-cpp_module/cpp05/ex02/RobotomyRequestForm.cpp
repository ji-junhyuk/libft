//
// Created by ji junhyuk on 2023/05/29.
//

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", false, 72, 45), mTarget("default") {
    std::cout << "[RobotomyRequestForm] Default constructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(std::string target) : AForm("RobotomyRequestForm", false, 72, 45), mTarget(target) {
    std::cout << "[RobotomyRequestForm] Single Argument constructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) : AForm(other.getName(), other.isSigned(), other.getRequiredSign(), other.getRequiredExec()), mTarget(other.mTarget) {
    std::cout << "[RobotomyRequestForm] Copy constructor called" << std::endl;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other) {
    std::cout << "[RobotomyRequestForm] Copy assignment constructor called" << std::endl;
    if (this != &other)
    {
       AForm::operator=(other);
       mTarget = other.mTarget;
    }
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {
    std::cout << "[RobotomyRequestForm] Destructor called" << std::endl;
}

void RobotomyRequestForm::execute(const Bureaucrat &executor) const {
    if (this->getRequiredExec() < executor.getGrade())
        throw Bureaucrat::GradeTooLowException();
    srand(time(NULL));
    if (rand() % 2 == 0)
        std::cout << mTarget << " has been robotomized." << std::endl;
    else
        std::cout << mTarget << " robotomy failed." << std::endl;
}
