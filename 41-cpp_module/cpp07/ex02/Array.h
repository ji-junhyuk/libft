#ifndef CPP07_ARRAY_H
#define CPP07_ARRAY_H

#include <exception>

template <typename T>
class Array {

private:
    unsigned int mSize;
    T* mArray;

public:
    Array();
    Array(unsigned int n);
    Array(const Array& other);
    Array& operator=(const Array& other);
    ~Array();

    T& operator[](unsigned int i) const;
    unsigned int size() const;

public:
    class OutOfBoundException : public std::exception {
        virtual const char* what(void) const throw() {
            return "OutOfBound";
        }
    };
};

#include "Array.tpp"

#endif //CPP07_ARRAY_H
