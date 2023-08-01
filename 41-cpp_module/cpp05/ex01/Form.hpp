#ifndef CPP05_FORM_HPP
#define CPP05_FORM_HPP


#include <string>
#include <iostream>

class Bureaucrat;
class Form {

private:
    const std::string mName;
    bool mbSigned;

private:
    const int mRequiredSign;
    const int mRequiredExec;

public:
    const std::string &getName() const;
    bool isSigned() const;
    int getRequiredSign() const;
    int getRequiredExec() const;

public:
    Form();
    Form(const std::string name, bool isSigned, const int gradeSign, const int gradeExec);
    Form(const Form& other);
    Form& operator=(const Form& other);
    ~Form();

    void beSigned(Bureaucrat &bure);

public:
    class GradeTooHighException : public std::exception {
    public:
        virtual const char *what() const throw();
    };
    class GradeTooLowException : public std::exception {
    public:
        virtual const char *what() const throw();
    };
};

std::ostream &operator<<(std::ostream &os, const Form &form);

#endif //CPP05_FORM_HPP
