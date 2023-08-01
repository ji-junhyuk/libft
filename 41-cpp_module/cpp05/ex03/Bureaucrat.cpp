//
// Created by ji junhyuk on 2023/05/26.
//

#include "Bureaucrat.hpp"


Bureaucrat::Bureaucrat() : mName("default"), mGrade(150) {
    std::cout << "[Bureaucrat] Default Constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(const std::string name, int grade) : mName(name), mGrade(grade) {
    if (mGrade < 1)
        throw GradeTooHighException();
    if (mGrade > 150)
        throw GradeTooLowException();
    std::cout << "[Bureaucrat] Single argument Constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : mName(other.mName), mGrade(other.mGrade) {
    std::cout << "[Bureaucrat] Copy Constructor called" << std::endl;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other) {
    std::cout << "[Bureaucrat] Copy assignment Constructor called" << std::endl;
    if (this != &other) {
        mGrade = other.mGrade;
    }
    return *this;
}

Bureaucrat::~Bureaucrat() {
    std::cout << "[Bureaucrat] Destructor called" << std::endl;
}

const std::string &Bureaucrat::getName() const {
    return mName;
}

int Bureaucrat::getGrade() const {
    return mGrade;
}


void Bureaucrat::increaseGrade() {
    if (mGrade <= 1) {
        throw GradeTooHighException();
    }
    --mGrade;
}

void Bureaucrat::decreaseGrade() {
    if (mGrade >= 150) {
        throw GradeTooLowException();
    }
    ++mGrade;
}

void Bureaucrat::signForm(AForm& form) {
    try {
        if (form.isSigned()) {
            std::cout << mName << " couldn't sign " << form.getName() << " because already signed" << std::endl;
        }
        else {
            form.beSigned(*this);
            std::cout << mName << " signed " << form.getName() << std::endl;
        }
    } catch (const std::exception &e) {
        std::cout << mName << " couldn't sign " << form.getName() << " because " << e.what() << std::endl;
    }
}

void Bureaucrat::executeForm(const AForm &form) const {
    try {
        if (form.isSigned()) {
            form.execute(*this);
        }
        else {
            std::cout << mName << " couldn't execute " << form.getName() << " because is not signed" << std::endl;
        }
    } catch (const std::exception &e) {
        std::cout << mName << " couldn't execute " << form.getName() << " because " << e.what() << std::endl;
    }
}

const char *Bureaucrat::GradeTooHighException::what() const throw() {
    return "Grade is too high.";
}

const char *Bureaucrat::GradeTooLowException::what() const throw() {
    return "Grade is too low.";
}

std::ostream &operator<<(std::ostream &os, const Bureaucrat &bureaucrat) {
    return os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << std::endl;
}
