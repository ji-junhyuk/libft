#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
    mBitCoinPriceCollection = other.mBitCoinPriceCollection;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other)
        mBitCoinPriceCollection = other.mBitCoinPriceCollection;
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
            year = strtol(token.c_str(), NULL, 10);
        else if (i == 1)
            month = strtol(token.c_str(), NULL, 10);
        else if (i == 2)
            date = strtol(token.c_str(), NULL, 10);
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
    if (*endPtr)
        throw InvalidDataFormat();
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
            std::string::size_type spacePos = key.find(' ');
            while (spacePos != std::string::npos) {
                key.erase(spacePos, 1);
                spacePos = key.find(' ');
            }
            std::string value = line.substr(pos + 1);
            spacePos = value.find(' ');
            while (spacePos != std::string::npos) {
                value.erase(spacePos, 1);
                spacePos = value.find(' ');
            }
            checkValidKey(key);
            checkValidValue(value);
            std::map<std::string, double>::iterator it = mBitCoinPriceCollection.find(key);
            if (it != mBitCoinPriceCollection.end()) {
                std::cout << key << " => " << value << " = " << it->second * strtod(value.c_str(), NULL) << std::endl;
            } else {
                std::map<std::string, double>::iterator upperBound = mBitCoinPriceCollection.upper_bound(key);
                    if (upperBound == mBitCoinPriceCollection.begin())
                       throw TooEarlyDate();
                    --upperBound;
                    std::cout << key << " => " << value << " = " << upperBound->second * strtod(value.c_str(), NULL) << std::endl;
            }
        } catch (const InvalidDataFormat& e) {
            std::cout << e.what() << line << std::endl;
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
}

const char *BitcoinExchange::InvalidDataFormat::what() const throw() {
    return "Error: bad input => ";
}

const char *BitcoinExchange::TooLargeNumber::what(void) const throw() {
    return "Error: too large a number.";
}

const char *BitcoinExchange::NotPositiveNumber::what(void) const throw() {
    return "Error: not a positive number.";
}

const char *BitcoinExchange::TooEarlyDate::what(void) const throw() {
    return "Error: date too early to provide";
}
