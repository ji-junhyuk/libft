#ifndef CPP08_SPAN_H
#define CPP08_SPAN_H

#include <vector>

template <typename T>
class Span {

private:
    unsigned int mCapacity;
    unsigned int mSize;
    std::vector<T> mNumbers;

public:
    Span();
    Span(unsigned int N);
    Span(const Span& other);
    Span& operator=(const Span& other);
    ~Span();

    void addNumber(const T& number);
    template <typename It>
    void addNumber(It start, It end);
    T shortestSpan() const;
    T longestSpan() const;
    unsigned int size() const;

public:
    class SpanIsFulled : public std::exception {
        virtual const char* what(void) const throw();
    };
    class NotEnoughSpan : public std::exception {
        virtual const char* what(void) const throw();
    };
};

#include "Span.tpp"

#endif //CPP08_SPAN_H
