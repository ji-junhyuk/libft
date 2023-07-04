#include "Convertor.h"

void Convertor::convert(const char* str) {
    char *dEndPtr = NULL;
    char *lEndPtr = NULL;
    long longValue = 0;
    double doubleValue = 0;

    doubleValue = strtod(str, &dEndPtr);
    longValue = strtol(str, &lEndPtr, 10);

    checkValidArgument(dEndPtr, str);

    printChar(lEndPtr, longValue);
    printInt(lEndPtr, longValue);
    std::cout << std::fixed << std::setprecision(1);
    printFloat(doubleValue);
    printDouble(doubleValue);
}

void Convertor::checkValidArgument(const char *str, const char *base_str) {
    if (*str) {
        if (strlen(base_str) == 1 && isprint(*base_str)) {
            std::cout << "char: " << *str << '\n';
            std::cout << "int: impossible" << '\n';
            std::cout << "float: impossible" << '\n';
            std::cout << "double: impossible" << '\n';
            exit(0);
        }
        if (!(!strcmp(str, "f") || !strcmp(str, "F"))) {
            std::cout << "char: impossible" << '\n';
            std::cout << "int: impossible" << '\n';
            std::cout << "float: impossible" << '\n';
            std::cout << "double: impossible" << '\n';
            exit(0);
        }
    }
}

void Convertor::printChar(const char *str, long &value) {
    if (value < std::numeric_limits<char>::min()
        || value > std::numeric_limits<char>::max()) {
        std::cout << "char: impossible" << std::endl;
        return ;
    }
    if (*str && value == 0) {
        std::cout << "char: impossible" << std::endl;
        return ;
    }
    if (isprint(value))
        std::cout << "char: " << static_cast<char>(value) << std::endl;
    else
        std::cout << "char: Non displayable"  << std::endl;
}

void Convertor::printInt(const char *str, long &value) {
    if (value < std::numeric_limits<int>::min()
        || value > std::numeric_limits<int>::max()) {
        std::cout << "int: impossible" << std::endl;
        return ;
    }
    if (*str && value == 0) {
        std::cout << "int: impossible" << std::endl;
        return ;
    }
    std::cout << "int: " << static_cast<int>(value) << std::endl;
}

void Convertor::printFloat(double &value) {
    std::cout << "float: " << static_cast<float>(value) << 'f' << '\n';
}

void Convertor::printDouble(double &value) {
    std::cout << "double: " << value << '\n';
}


