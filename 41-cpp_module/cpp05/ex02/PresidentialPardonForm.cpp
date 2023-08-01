//
// Created by ji junhyuk on 2023/05/29.
//

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPardonForm", false, 25, 5), mTarget("default") {
    std::cout << "[PresidentialPardonForm] Default constructor called" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(std::string target) : AForm("PresidentialPardonForm", false, 25, 5), mTarget(target) {
    std::cout << "[PresidentialPardonForm] Single argument constructor called" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other) : AForm(other.getName(), other.isSigned(), other.getRequiredSign(), other.getRequiredExec()), mTarget(other.mTarget) {
    std::cout << "[PresidentialPardonForm] Copy constructor called" << std::endl;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &other) {
    std::cout << "[PresidentialPardonForm] Copy assignment constructor called" << std::endl;
    if (this != &other) {
        AForm::operator=(other);
        mTarget = other.mTarget;
    }
    return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {
    std::cout << "[PresidentialPardonForm] Destructor called" << std::endl;
}

void PresidentialPardonForm::execute(const Bureaucrat &executor) const {
    if (!this->isSigned())
        throw Bureaucrat::IsNotSignedException();
    if (this->getRequiredExec() < executor.getGrade())
        throw Bureaucrat::GradeTooLowException();
    std::cout << mTarget << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}

