#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
    BitcoinExchange B;
    B.setPriceBitcoin();
    if (argc == 2) {
        B.calculateBitcoinPrice(argv[1]);
    }
}
