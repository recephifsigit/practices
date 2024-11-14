#include <iostream>
#include <cstdint>

class MyClass {
    public:
    uint32_t return10() const { return 10; }
};
uint32_t operator+(const MyClass& a, uint32_t b) { return a.return10() + b; }      // bu  (MyClass, int) durumlarinda gecerli
uint32_t operator+(uint32_t lhs, const MyClass& a) { return lhs + a.return10(); }  // bu  (int, MyClass) durumlarinda gecerli

class InClassOperator {
    public:
    uint32_t g = 0;
    uint32_t return10() const { return 10; }
    uint32_t operator+(uint32_t b) const { return return10() + b; }  // bu  (InClassOperator, int) durumlarinda gecerli
    uint32_t& operator[](uint32_t i) {
        std::cout << "operator[" << i << "]" << std::endl;
        return ++g;
    }
};
uint32_t operator+(uint32_t lhs, const InClassOperator& rhs) { return lhs + rhs.return10(); }  // bu  (int, InClassOperator) durumlarinda gecerli ama global operator+ olmali

void globalOperatorFunctionExample() {
    MyClass a;
    std::cout << (5 + a) << std::endl;
    std::cout << (a + 20) << std::endl;
}

void inClassOperatorFunctionExample() {
    InClassOperator d;
    std::cout << (d + 7) << std::endl;
    std::cout << (7 + d) << std::endl;
}

void addressOperatorFunctionExample() {
    InClassOperator d;

    for (uint8_t i = 0; i < 10; i++) {
        std::cout << d[i] << std::endl;
    }
}

// simetrik operatorlerin global olmasi daha mantiklidir (+ - * / % << >> == != < > <= >=)
// sinif nesnesini degistiren operatorler uye operator function olmasi daha mantiklidir

// using bildirimini global alanlarda kullanmak pek mantikli degil

// dummy parametrelere isim vermeye gerk yok kalite kontrole takilmasin  void func(int a, int);

int main() {
    globalOperatorFunctionExample();
    inClassOperatorFunctionExample();
    addressOperatorFunctionExample();
    return 0;
}
