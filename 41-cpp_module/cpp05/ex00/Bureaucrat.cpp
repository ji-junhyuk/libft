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
    std::cout << "[Bureaucrat] Two argument Constructor called" << std::endl;
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

const char *Bureaucrat::GradeTooHighException::what() const throw() {
    return "Grade is too high.";
}

const char *Bureaucrat::GradeTooLowException::what() const throw() {
    return "Grade is too low.";
}

std::ostream& operator<<(std::ostream &os, const Bureaucrat &bureaucrat) {
    return os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << std::endl;
}
