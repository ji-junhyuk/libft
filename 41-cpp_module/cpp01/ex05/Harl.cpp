//
// Created by Junhyuk Ji on 3/9/23.
//

#include "Harl.hpp"

void Harl::debug(void) {
    std::cout << "[DEBUG]: I love having extra bacon for my 7XL-double-cheese-triple-pickle-special- ketchup burger. I really do!" << '\n';
}

void Harl::info(void) {
    std::cout << "[INFO]: I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << '\n';
}

void Harl::warning(void) {
    std::cout << "[WARNING]: I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month." << '\n';
}

void Harl::error(void) {
    std::cout << "[ERROR]: This is unacceptable! I want to speak to the manager now." << '\n';
}

int Harl::GenerateHash(const char *key) {
    unsigned long hash = 5381;
    while (*key)
    {
        hash = (((hash << 5) + hash) + *key) % mTableSize;
        key++;
    }
    return hash % mTableSize;
}

void Harl::SetHashTable() {
    mFp[2] = &Harl::debug;
    mFp[6] = &Harl::info;
    mFp[5] = &Harl::warning;
    mFp[1] = &Harl::error;
}

void Harl::Complain(std::string level) {
    if (std::find(mFunctionTables, mFunctionTables + 4, level) == mFunctionTables + 4)
    {
        std::cout << "No function pointers assigned." << '\n';
        return ;
    }
    const char *key = level.c_str();
    (this->*mFp[GenerateHash(key)])();
}
