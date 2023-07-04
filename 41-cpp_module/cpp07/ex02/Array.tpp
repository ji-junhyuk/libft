#ifndef CPP07_ARRAY_TPP
#define CPP07_ARRAY_TPP

#include "Array.h"

template <typename T>
Array<T>::Array() : mSize(0), mArray(new T[0]) {
}

template <typename T>
Array<T>::Array(unsigned int n) : mSize(n), mArray(new T[n]) {
}

template <typename T>
Array<T>::Array(const Array& other) : mSize(other.mSize), mArray(new T[other.mSize]) {
    for (unsigned int i = 0; i < mSize; ++i) {
        mArray[i] = other.mArray[i];
    }
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        delete[] mArray;
        mArray = new T[other.mSize];
        mSize = other.mSize;
        for (unsigned int i = 0; i < mSize; ++i) {
            mArray[i] = other.mArray[i];
        }
    }
    return (*this);
}

template <typename T>
Array<T>::~Array() {
    delete[] mArray;
}

template <typename T>
T& Array<T>::operator[](unsigned int i) const {
    if (i >= mSize || i < 0)
        throw OutOfBoundException();
    return mArray[i];
}

template <typename T>
unsigned int Array<T>::size() const {
    return mSize;
}

#endif //CPP07_ARRAY_TPP
