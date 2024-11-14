#include <iostream>
#include <memory>
#include <string>

void AsteriskOperatorExample() {
    class SmartString {
        public:
        explicit SmartString(std::unique_ptr<std::string> p) : mp{std::move(p)} { std::cout << "Constructor created\n"; }

        ~SmartString() { std::cout << "Destructor called\n"; }

        const std::string& operator*() const { return *mp; }

        private:
        std::unique_ptr<std::string> mp;
    };

    SmartString ptr{std::make_unique<std::string>("abc")};
    std::cout << "String:      " << *ptr << "\n";
    std::cout << "String size: " << (*ptr).size() << "\n";

    for (char ch : *ptr) {
        std::cout << ch << "\n";
    }
}

void ArrowOperatorExample() {
    class InnerClass {
        public:
        void SayHello() const { std::cout << "Hello from InnerClass\n"; }
    };

    class WrapperClass {
        public:
        const InnerClass* operator->() const { return &inner; }

        private:
        InnerClass inner;
    };

    WrapperClass wrapper;
    wrapper->SayHello();
}

void MakeUniqueExample() {
    auto myptrstring = std::make_unique<std::string>("UniquePtrStringContent");
    std::cout << "Unique Ptr String: " << *myptrstring << "\n";
}

void FunctionCallOperatorExample() {
    class CallableClass {
        public:
        explicit CallableClass(int a) : mx{a} { std::cout << "CallableClass initialized with value: " << a << "\n"; }

        void operator()(int x) const {
            std::cout << "int version called\n";
            for (int i = mx; i < mx + x; ++i) {
                std::cout << i << "\n";
            }
        }

        void operator()(uint8_t x) const {
            std::cout << "uint8_t version called\n";
            for (int i = mx; i < mx + x; ++i) {
                std::cout << i << "\n";
            }
        }

        void operator()(double x) const {
            std::cout << "double version called\n";
            for (int i = mx; i < mx + static_cast<int>(x); ++i) {
                std::cout << i << "\n";
            }
        }

        private:
        int mx;
    };

    CallableClass callable(10);
    callable(5);    // int version
    callable(5.6);  // double version
}

void TypeCastOperatorExample() {
    class TypeCastClass {
        public:
        operator int() const {
            std::cout << "int typecast called\n";
            return 0;
        }
        operator double() const {
            std::cout << "double typecast called\n";
            return 0.0;
        }
    };

    TypeCastClass myclass;
    int ival = myclass;      // Implicit int cast
    double dival = myclass;  // Implicit double cast
}

void BoolOperatorExample() {
    class BoolClass {
        public:
        explicit operator bool() const {
            std::cout << "bool operator called\n";
            return false;
        }
    };

    BoolClass mybool;

    if (mybool) {
        std::cout << "Bool operator evaluated to true\n";
    } else {
        std::cout << "Bool operator evaluated to false\n";
    }
}

int main() {
    AsteriskOperatorExample();
    ArrowOperatorExample();
    MakeUniqueExample();
    FunctionCallOperatorExample();
    TypeCastOperatorExample();
    BoolOperatorExample();
    return 0;
}
