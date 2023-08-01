//
// Created by ji junhyuk on 2023/05/28.
//

#include "AForm.hpp"
#include "Bureaucrat.hpp"

const std::string &AForm::getName() const {
    return mName;
}

bool AForm::isSigned() const {
    return mbSigned;
}

int AForm::getRequiredSign() const {
    return mRequiredSign;
}

int AForm::getRequiredExec() const {
    return mRequiredExec;
}

AForm::AForm() : mName("default"), mbSigned(false), mRequiredSign(150), mRequiredExec(150)  {
    std::cout << "[AForm] Default constructor called" << std::endl;
}

AForm::AForm(const std::string name, bool isSigned, const int gradeSign, const int gradeExec) : mName(name), mbSigned(isSigned), mRequiredSign(gradeSign), mRequiredExec(gradeExec) {
    std::cout << "[AForm] Four argument constructor called" << std::endl;
}

AForm::AForm(const AForm& other) : mName(other.mName), mbSigned(other.mbSigned), mRequiredSign(other.mRequiredSign), mRequiredExec(other.mRequiredExec) {
    std::cout << "[AForm] Copy constructor called" << std::endl;
}

AForm &AForm::operator=(const AForm& other) {
    std::cout << "[AForm] Copy assignment constructor called" << std::endl;
    if (this != &other) {
        mbSigned = other.mbSigned;
    }
    return *this;
}

AForm::~AForm() {
    std::cout << "[AForm] Destructor called" << std::endl;
}

void AForm::beSigned(Bureaucrat& bure) {
    if (bure.getGrade() > mRequiredSign)
        throw AForm::GradeTooLowException();
    mbSigned = true;
}

const char *AForm::GradeTooHighException::what() const throw() {
    return "Form Grade is too high.";
}

const char *AForm::GradeTooLowException::what() const throw() {
    return "Form Grade is too low.";
}

std::ostream& operator<<(std::ostream& os, const AForm& form) {
    return os << form.getName()
    << (form.isSigned() ? ", is signed" : ", not signed") << ", required grade for sign: "
    << form.getRequiredSign() << ", required grade for exec: "
    << form.getRequiredExec() << std::endl;
}
