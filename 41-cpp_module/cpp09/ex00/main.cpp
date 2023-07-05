//
// Created by ji junhyuk on 2023/06/03.
//

#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
    (void )argv;
    BitcoinExchange B;
    B.setPriceBitcoin();
    if (argc == 2) {
        try {
            B.calculateBitcoinPrice(argv[1]);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
}
