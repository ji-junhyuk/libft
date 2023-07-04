#include <iostream>
#include "Span.h"

int main() {
    Span<int> span(10);
    span.addNumber(2);
    span.addNumber(4);
    span.addNumber(6);
    span.addNumber(8);
    int numbers[] = {10, 12, 14, 16};
    span.addNumber(numbers, numbers + sizeof(numbers) / sizeof(int));
    int shortest = span.shortestSpan();
    std::cout << "shortest: " << shortest << std::endl;
    int longest = span.longestSpan();
    std::cout << "longest: " << longest << std::endl;


    Span<double> span3(5);

    span3.addNumber(3.1);
    span3.addNumber(4.2);
    span3.addNumber(5.3);
    span3.addNumber(6.4);
    span3.addNumber(7.5);

    double shortest2 = span3.shortestSpan();
    double longest2 = span3.longestSpan(); std::cout << "longest: " << longest2 << std::endl; std::cout << "shortest: " << shortest2 << std::endl;

    Span<int> span4(1);
    try {
        span4.addNumber(numbers, numbers + sizeof(numbers) / sizeof(int));
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    try {
        int shortest4 = span4.shortestSpan();
        std::cout << shortest4 << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    try {
        int longest4 = span4.longestSpan();
        std::cout << longest4 << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

}
