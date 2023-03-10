//
// Created by Junhyuk Ji on 3/9/23.
//

#ifndef INC_42COURSE_HARL_HPP
#define INC_42COURSE_HARL_HPP

#include <string>
#include <iostream>

class Harl {

private:
    int mTableSize;
    std::string mFunctionTables[4];
    void debug(void);
    void info(void);
    void warning(void);
    void error(void);
    void (Harl::*mFp[7])();

public:
    Harl() : mTableSize(7) {
        mFunctionTables[0] = "DEBUG";
        mFunctionTables[1] = "INFO";
        mFunctionTables[2] = "WARNING";
        mFunctionTables[3] = "ERROR";
        SetHashTable();
    }
    int GenerateHash(const char *key);
    void Complain(std::string level);
    void SetHashTable();
};

#endif //INC_42COURSE_HARL_HPP