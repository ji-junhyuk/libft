//
// Created by ji junhyuk on 2023/06/03.
//

#ifndef CPP09_BITCOINEXCHANGE_H
#define CPP09_BITCOINEXCHANGE_H

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
    void isValidKey(const std::string &str);
    void isValidValue(const std::string &str);
public:
//    class Error : public std::exception {
//    public:
//        Error(const std::string& message, const std::string& key);
//        virtual const char* what() const throw();
//
//    private:
//        std::string errorMessage;
//        std::string errorKey;
//    };
    class InvalidDataFormat : public std::exception {
        virtual const char *what() const throw();
    };

    class TooLargeNumber : public std::exception {
        virtual const char *what() const throw();
    };

    class NotPositiveNumber : public std::exception {
        virtual const char *what() const throw();
    };

};


#endif //CPP09_BITCOINEXCHANGE_H
