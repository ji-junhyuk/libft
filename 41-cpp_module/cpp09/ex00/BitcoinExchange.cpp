//
// Created by ji junhyuk on 2023/06/03.
//

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
    (void) other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    (void) other;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {

}

void BitcoinExchange::setPriceBitcoin() {
    std::ifstream file("data.csv");

    if (!file) {
        std::cerr << "cannot open file." << std::endl;
        return ;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        size_t pos = line.find( ',');
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        mBitCoinPriceCollection[key] = std::strtod(value.c_str(), NULL);
//        if (pos == std::string::npos) {
//            throw InvalidDataFormat();
//        }
//        else {
//            std::cout << key << ' ' << value << '\n';
//            checkValidKey(key);
//            checkValidValue(value);
//            std::cout << key << ' ' << value << '\n';
//        }
    }
}

void BitcoinExchange::checkValidKey(const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    int year = 0, month = 0, date = 0, days = 0;
    bool isLeapYear = false;

    int i = 0;
    while (std::getline(iss, token, '-')) {
        if (i == 0)
            year = std::stoi(token);
        else if (i == 1)
            month = std::stoi(token);
        else if (i == 2)
            date = std::stoi(token);
        else
            throw InvalidDataFormat();
       ++i;
    }
    if (year < 2009 || year > 2022) {
        throw InvalidDataFormat();
    }
    if (month < 1 || month > 12) {
        throw InvalidDataFormat();
    }
    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    days = daysInMonth[month - 1];
    if ((year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
        isLeapYear = true;
    }
    if (month == 2 && isLeapYear) {
        days = 29;
    }
    if (date < 1 || date > days) {
        throw InvalidDataFormat();
    }
}

void BitcoinExchange::checkValidValue(const std::string &str) {
    std::ostringstream oss;
    char* endPtr;
    double value = strtod(str.c_str(), &endPtr);
    std::cout << "value: " << value << std::endl;
    if (*endPtr) {
        std::cout << endPtr << std::endl;
        throw InvalidDataFormat();
    }
    if (value < 0)
        throw NotPositiveNumber();
    else if (value > 1000)
        throw TooLargeNumber();
}

void BitcoinExchange::calculateBitcoinPrice(const char *fileName) {
    std::ifstream file(fileName);

    if (!file) {
        std::cerr << "cannot open file." << std::endl;
        return ;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        size_t pos = line.find('|');
        try {
            if (pos == std::string::npos)
                throw InvalidDataFormat();
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            checkValidKey(key);
            checkValidValue(value);
            mBitCoinPriceCollection[key] = std::strtod(value.c_str(), NULL);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
}

const char *BitcoinExchange::InvalidDataFormat::what() const throw() {
    return key.c_str();//"Error: bad input => ";
}

const char *BitcoinExchange::TooLargeNumber::what(void) const throw() {
    return "Error: too large a number.";
}

const char *BitcoinExchange::NotPositiveNumber::what(void) const throw() {
    return "Error: not a positive number.";
}
