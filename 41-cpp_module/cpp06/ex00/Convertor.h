#ifndef CPP06_CONVERTOR_H
#define CPP06_CONVERTOR_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>

class Convertor {

public:
    Convertor();
    Convertor(const Convertor& other);
    Convertor& operator=(const Convertor& other);
    ~Convertor();

    static void printDouble(double &value);
    static void printFloat(double &value);
    static void printInt(const char *str, long &value);
    static void printChar(const char *str, long &value);
    static void checkValidArgument(const char *str, const char *base_str);
    static void convert(const char *str);
};


#endif //CPP06_CONVERTOR_H
