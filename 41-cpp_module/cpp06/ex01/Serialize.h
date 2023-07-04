#ifndef CPP06_SERIALIZE_H
#define CPP06_SERIALIZE_H

#include <cstdint>
#include "Data.h"

class Serialize {

public:
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);

    Serialize();
    Serialize(const Serialize& other);
    Serialize& operator=(const Serialize& other);
    ~Serialize();
};


#endif //CPP06_SERIALIZE_H
