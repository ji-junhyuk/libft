#include "Data.h"

Data::Data() : mInt(1918), mName("hello") {

}

Data::Data(const Data &other) : mInt(other.mInt), mName(other.mName) {

}

Data &Data::operator=(const Data &other) {
    if (this != &other)
    {
        mInt = other.mInt;
        mName = other.mName;
    }
    return *this;
}

Data::~Data() {

}

unsigned int Data::getInt() const {
    return mInt;
}

const std::string &Data::getName() const {
    return mName;
}
