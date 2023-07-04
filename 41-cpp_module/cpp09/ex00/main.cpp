//
// Created by ji junhyuk on 2023/06/03.
//

#include "BitcoinExchange.h"

int main(int argc, char *argv[])
{
    (void )argv;
    BitcoinExchange B;
    try {
        B.setPriceBitcoin();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    if (argc == 2) {

    } else {
        std::cerr << "Error: could not open file." << std::endl;
    }
}
