#include "Span.h"

template <typename T>
Span<T>::Span() : mCapacity(0), mSize(0) {

}

template <typename T>
Span<T>::Span(unsigned int N) : mCapacity(N), mSize(0) {

}

template <typename T>
Span<T>::Span(const Span& other) : mCapacity(other.mCapacity), mSize(other.mSize), mNumbers(other.mNumbers) {

}

template <typename T>
Span<T>& Span<T>::operator=(const Span& other) {
    if (this != &other) {
        mCapacity = other.mCapacity;
        mSize = other.mSize;
        mNumbers = other.mNumbers;
    }
    return *this;
}

template <typename T>
Span<T>::~Span() {

}

template <typename T>
void Span<T>::addNumber(const T& number) {
    if (mNumbers.size() >= mCapacity) {
        throw SpanIsFulled();
    }
    mNumbers.push_back(number);
    ++mSize;
}

template <typename T>
template <typename It>
void Span<T>::addNumber(It start, It end) {
    while (start != end) {
        addNumber(*start);
        ++start;
        ++mSize;
    }
}

template <typename T>
T Span<T>::shortestSpan() const {
    if (mNumbers.size() < 2) {
        throw NotEnoughSpan();
    }
    std::vector<T> sortedNumbers(mNumbers);
    std::sort(sortedNumbers.begin(), sortedNumbers.end());
    T shortest = std::numeric_limits<T>::max();
    for (unsigned int i = 1; i < sortedNumbers.size(); ++i) {
        T distance = sortedNumbers[i] - sortedNumbers[i - 1];
        if (distance < shortest) {
            shortest = distance;
        }
    }
    return shortest;
}

template <typename T>
T Span<T>::longestSpan() const {
    if (mNumbers.size() < 2) {
        throw NotEnoughSpan();
    }
    std::vector<T> sortedNumbers(mNumbers);
    std::sort(sortedNumbers.begin(), sortedNumbers.end());
    return sortedNumbers[sortedNumbers.size() - 1] - sortedNumbers[0];
}

template <typename T>
const char* Span<T>::SpanIsFulled::what() const throw() {
    return "Span is fulled";
}

template <typename T>
const char* Span<T>::NotEnoughSpan::what() const throw() {
    return "Not enough numbers to find";
}

template <typename T>
unsigned int Span<T>::size() const {
    return mSize;
}