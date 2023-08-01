//
// Created by ji junhyuk on 2023/05/29.
//

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", false, 145, 137), mTarget("default") {
    std::cout << "[Shrubbery] Default constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("ShrubberyCreationForm", false, 145, 137), mTarget(target) {
    std::cout << "[Shrubbery] Single argument constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) : AForm(other.getName(), other.isSigned(), other.getRequiredSign(), other.getRequiredExec()) {
    std::cout << "[Shrubbery] Copy constructor called" << std::endl;
    mTarget = other.mTarget;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
    std::cout << "[Shrubbery] Copy assignment constructor called" << std::endl;
    if (this != &other) {
        AForm::operator=(other);
        mTarget = other.mTarget;
    }
    return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
    std::cout << "[Shrubbery] Destructor called" << std::endl;
}

void ShrubberyCreationForm::execute(const Bureaucrat &executor) const {
    std::string filename;
    std::ofstream file;

    if (this->getRequiredExec() < executor.getGrade())
        throw Bureaucrat::GradeTooLowException();
    filename = mTarget;
    filename.append("_shrubbery");
    file.open(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Failed to open file file" << std::endl;
        return ;
    }
    file << "        *        " << std::endl;
    file << "       / \\       " << std::endl;
    file << "      /   \\      " << std::endl;
    file << "     /     \\     " << std::endl;
    file << "    /       \\    " << std::endl;
    file << "   /_________\\   " << std::endl;
    file << "       |||||      " << std::endl;
    file << "       |||||      " << std::endl;
    file.close();
    executor.getName();
}
