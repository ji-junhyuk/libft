#include <iostream>

class Base {
public:
    int baseValue;

    Base(int value) : baseValue(value) {}

    void print() {
        std::cout << "Base: " << baseValue << std::endl;
    }
};

class Derived : public Base {
public:
    int derivedValue;

    Derived(int base, int derived) : Base(base), derivedValue(derived) {}

    void print() {
        std::cout << "Derived: " << baseValue << ", " << derivedValue << std::endl;
    }
};

int main() {
    Derived derived(10, 20);
    Base base = derived;  // 파생 클래스 객체를 기본 클래스 객체로 복사

    base.print();  // 기본 클래스의 print() 함수 호출

    return 0;
}
