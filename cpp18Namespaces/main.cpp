#include <iostream>
#include <string>

void IntegralPromotion() {
    // İç sınıf örneği
    class MyClass {
        public:
        operator bool() const {
            std::cout << "bool func entered!\n";
            return true;
        }
    };

    MyClass my, m1;
    auto result = my + m1;  // Implicit dönüşüm: MyClass -> bool -> int (integral promotion)
    std::cout << "Result of integral promotion: " << result << "\n";
}

// Namespace örnekleri
namespace ali {
    int func() { return 50; }
    int a = 746;

    namespace veli {
        int func() { return 10; }
        int a = 0;
    }
}

namespace master {
    int ambiguity = 9;
    int x = 9;
}

namespace injected {
    using master::x;  // master namespace'inden x'i erişilebilir hale getirir
}

namespace globalMaster {
    int x, y, z;
}
namespace globalInjected {
    using namespace globalMaster;  // GlobalMaster'dan isimler inject edilir
    int x = 889;
}

void namespaceExamples() {
    std::cout << "ali::func(): " << ali::func() << "\n";
    std::cout << "ali::veli::func(): " << ali::veli::func() << "\n";
}

void usingExample() {
    using ali::a;
    std::cout << "Value of ali::a via 'using': " << a << "\n";
}

// Argument Dependent Lookup örneği
namespace argDepLookup1 {
    class A {};
    void func(const A&) { std::cout << "ADL: Function in argDepLookup1 called.\n"; }
}
namespace argDepLookup2 {
    class B {};
    void func(const B&) { std::cout << "ADL: Function in argDepLookup2 called.\n"; }
}

// Sınıf örneği
class ExampleClass {
    public:
    ExampleClass myfunc() { return *this; }
    int sum() { return 12; }
};

int main() {
    // Integral promotion örneği
    IntegralPromotion();

    // Namespace örnekleri
    namespaceExamples();
    usingExample();

    // master namespace'den x değerini değiştir
    master::x = 19;
    std::cout << "master::x: " << master::x << "\n";

    // Global injected örneği
    using globalInjected::x;
    std::cout << "globalInjected::x: " << globalInjected::x << "\n";

    // Argument Dependent Lookup örneği
    argDepLookup1::A ax;
    argDepLookup2::B bx;
    func(ax);  // argDepLookup1::func çağrılır
    func(bx);  // argDepLookup2::func çağrılır

    // Sınıf kullanımı örneği
    ExampleClass exampleObj;
    auto newObj = exampleObj.myfunc();
    auto result = newObj.sum();
    std::cout << "Sum result: " << result << "\n";

    return 0;
}
