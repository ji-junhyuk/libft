#ifndef CPP09_BITCOINEXCHANGE_HPP
#define CPP09_BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>

class BitcoinExchange {

private:
    std::map<std::string, double> mBitCoinPriceCollection;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void setPriceBitcoin();
    void checkValidKey(const std::string &str);
    void checkValidValue(const std::string &str);
    void calculateBitcoinPrice(const char *fileName);
public:
    class InvalidDataFormat : public std::exception {
    public:
        virtual const char *what() const throw();
    };
    class TooLargeNumber : public std::exception {
    public:
        virtual const char *what() const throw();
    };
    class NotPositiveNumber : public std::exception {
    public:
        virtual const char *what() const throw();
    };
    class TooEarlyDate : public std::exception {
    public:
        virtual const char *what() const throw();
    };
};


#endif //CPP09_BITCOINEXCHANGE_HPP