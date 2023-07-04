#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Base.h"
#include "A.h"
#include "B.h"
#include "C.h"

static Base* generate(void)
{
    int num = rand() % 3;

    if (num == 0) {
        std::cout << "A is created" << std::endl;
        return new A();
    } else if (num == 1) {
        std::cout << "B is created" << std::endl;
        return new B();
    } else if (num == 2) {
        std::cout << "C is created" << std::endl;
        return new C();
    }
    return NULL;
}

static void identify(Base* p)
{
    if (dynamic_cast<A*>(p)) {
        std::cout << "Confirmed as A" << std::endl;
    } else if (dynamic_cast<B*>(p)) {
        std::cout << "Confirmed as B" << std::endl;
    } else if (dynamic_cast<C*>(p)) {
        std::cout << "Confirmed as C" << std::endl;
    } else {
        std::cout << "[*] Something went wrong" << std::endl;
    }
}

static void identify(Base& p)
{
    try {
        A& a = dynamic_cast<A&>(p);
        std::cout << "Confirmed as A" << std::endl;
        (void) a;
    } catch(const std::exception& e) {
        std::cout << "[&]Something went wrong" << std::endl;
    }
    try {
        B& b = dynamic_cast<B&>(p);
        std::cout << "Confirmed as B" << std::endl;
        (void) b;
    } catch(const std::exception& e) {
        std::cout << "[&]Something went wrong" << std::endl;
    }
    try {
        C& c = dynamic_cast<C&>(p);
        std::cout << "Confirmed as C" << std::endl;
        (void) c;
    } catch(const std::exception& e) {
        std::cout << "[&]Something went wrong" << std::endl;
    }
}

int main(void)
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    Base *p;

    p = generate();
    identify(p);
    identify(*p);
}