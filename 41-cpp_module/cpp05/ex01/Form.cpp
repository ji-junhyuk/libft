//
// Created by ji junhyuk on 2023/05/28.
//

#include "Form.hpp"
#include "Bureaucrat.hpp"

const std::string &Form::getName() const {
    return mName;
}

bool Form::isSigned() const {
    return mbSigned;
}

int Form::getRequiredSign() const {
    return mRequiredSign;
}

int Form::getRequiredExec() const {
    return mRequiredExec;
}

Form::Form() : mName("default"), mbSigned(false), mRequiredSign(150), mRequiredExec(150)  {
    std::cout << "[Form] Default constructor called" << std::endl;
}

Form::Form(const std::string name, bool isSigned, const int gradeSign, const int gradeExec) : mName(name), mbSigned(isSigned), mRequiredSign(gradeSign), mRequiredExec(gradeExec) {
    if (gradeSign < 1 || gradeExec < 1)
        throw GradeTooHighException();
    if (gradeSign > 150 || gradeExec > 150)
        throw GradeTooLowException();
    std::cout << "[Form] Four argument constructor called" << std::endl;
}

Form::Form(const Form &other) : mName(other.mName), mbSigned(other.mbSigned), mRequiredSign(other.mRequiredSign), mRequiredExec(other.mRequiredExec) {
    std::cout << "[Form] Copy constructor called" << std::endl;
}

Form &Form::operator=(const Form &other) {
    std::cout << "[Form] Copy assignment constructor called" << std::endl;
    if (this != &other) {
        mbSigned = other.mbSigned;
    }
    return *this;
}

Form::~Form() {
    std::cout << "[Form] Destructor called" << std::endl;
}

void Form::beSigned(Bureaucrat &bure) {
    if (bure.getGrade() > mRequiredSign) {
        throw Form::GradeTooLowException();
    }
    mbSigned = true;
}

const char *Form::GradeTooHighException::what() const throw() {
    return "Grade is too high.";
}

const char *Form::GradeTooLowException::what() const throw() {
    return "Grade is too low.";
}

std::ostream &operator<<(std::ostream &os, const Form &form) {
    return os << form.getName()
    << (form.isSigned() ? ", is signed" : ", not signed") << ", required grade for sign: "
    << form.getRequiredSign() << ", required grade for exec: "
    << form.getRequiredExec() << std::endl;
}
