#ifndef CPP06_DATA_H
#define CPP06_DATA_H

#include <iostream>

class Data {

private:
    unsigned int mInt;
    std::string mName;

public:
    unsigned int getInt() const;
    const std::string &getName() const;

    Data();
    Data(const Data& other);
    Data& operator=(const Data& other);
    ~Data();
};


#endif //CPP06_DATA_H
