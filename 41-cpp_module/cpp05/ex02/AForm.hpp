//
// Created by ji junhyuk on 2023/05/28.
//

#ifndef CPP05_FORM_HPP
#define CPP05_FORM_HPP


#include <string>
#include <iostream>

class Bureaucrat;
class AForm {

private:
    const std::string mName;
    bool mbSigned;
    const int mRequiredSign;
    const int mRequiredExec;

public:
    const std::string &getName() const;
    bool isSigned() const;
    int getRequiredSign() const;
    int getRequiredExec() const;

public:
    AForm();
    AForm(const std::string name, bool isSigned, const int gradeSign, const int gradeExec);
    AForm(const AForm& other);
    AForm& operator=(const AForm& other);
    virtual ~AForm();

    void beSigned(Bureaucrat &bure);
    virtual void execute(const Bureaucrat& executor) const = 0;

public:
    class GradeTooHighException : public std::exception {
        virtual const char *what() const throw();
    };
    class GradeTooLowException : public std::exception {
        virtual const char *what() const throw();
    };
};

std::ostream &operator<<(std::ostream &os, const AForm &form);



#endif //CPP05_FORM_HPP
