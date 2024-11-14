#include <cstdint>
#include <iostream>

class Myclass {
    public:
    Myclass() { std::cout << "Myclass()" << std::endl; }
    Myclass(int, int) { std::cout << "Myclass(int, int)" << std::endl; }
    void foo() { std::cout << "foo()" << std::endl; }
    void func(int, int) { std::cout << "func(int, int)" << std::endl; }
};

// Rvalue referans parametresi alan bir fonksiyona geçici nesne (temporary) gönderilebilir.
// Ancak, bir geçici nesne (Rvalue) Lvalue referans ile kabul edilemez.
void CopyElisionExample(Myclass &&) { std::cout << "CopyElisionExample(Myclass &&)" << std::endl; }

Myclass CopyElisionExample2() {
    std::cout << "CopyElisionExample2()" << std::endl;
    return Myclass();  // RVO (Return Value Optimization): Kopya yaratılmaz, nesne doğrudan dönüş konumunda oluşturulur.
}

Myclass CopyElisionExample3() {
    std::cout << "CopyElisionExample3()" << std::endl;
    Myclass obj;
    return obj;  // NRVO (Named Return Value Optimization): Kopyalama yapılmadan dönüş gerçekleşir.
}

// TEMPORARY MATERIALIZATION
/*
Temporary materialization, geçici nesnelerle güvenli işlem yapabilmek için gereklidir.
Geçici nesneler, yalnızca belirli bir işlemi gerçekleştirmek için anlık olarak oluşturulduklarından
normalde hızla yok edilirler. Ancak `const` referans bağlandığında veya bir fonksiyon parametresi olarak verildiğinde,
nesnenin ömrünün uzatılması gerekir. Bu durumda, geçici nesnenin bellekte güvenli bir şekilde varlığını
sürdürmesi için temporary materialization devreye girer.
*/
void TemporaryMaterialization() {
    std::cout << "TemporaryMaterialization()" << std::endl;
    const Myclass &a = Myclass{};  // Geçici nesne `const` referansa bağlanır ve ömrü uzatılır.
}

void TemporaryMaterialization2(const Myclass &param) {
    std::cout << "TemporaryMaterialization2()" << std::endl;
    // Geçici nesne, `param` için somutlaştırılır.
}

void ConversionConstructor() {
    /*
    Conversion constructor (dönüşüm kurucusu), bir sınıfın tek bir parametre alan ve başka bir türden gelen bir değeri
    o sınıfın bir nesnesine dönüştürmek için kullanılan özel bir kurucu fonksiyondur.
    Bu kurucular, türler arası otomatik veya isteğe bağlı dönüşümlere izin verir.
    */

    class MyClass {
        public:
        MyClass(int x) : value(x) { std::cout << "conversion ctor: " << value << std::endl; }  // Conversion constructor
        int value;
    };

    MyClass m = 10;  // `int` -> `MyClass` dönüşümü (Conversion constructor çağrılır)

    class MyClassExplicit {
        public:
        explicit MyClassExplicit(int x) : value(x) { std::cout << "conversion ctor explicit: " << value << std::endl; }  // `explicit` ile otomatik dönüşüm engellenir.
        int value;
    };

    MyClassExplicit obj2 = MyClassExplicit(10);  // Geçerli, açık dönüşüm
}

int main() {
    Myclass{};                 // Geçici nesne oluşturulur
    Myclass{}.foo();           // Geçici nesne üzerinden `foo()` çağrılır
    Myclass{1, 1};             // Geçici nesne oluşturulur
    Myclass{1, 1}.func(1, 1);  // Geçici nesne üzerinden `func()` çağrılır

    Myclass x;
    x = Myclass{};                  // Geçici nesnenin ömrü bulunduğu scope'un sonuna kadar sürer
    const Myclass &a = Myclass{};   // Geçici nesne referansa bağlanırsa, ömrü referans süresince devam eder.
                                    // `const Lvalue` referansa bağlanabilmesi için `Rvalue` olabilir.
    CopyElisionExample(Myclass{});  // Copy elision ile geçici nesne oluşturulup doğrudan fonksiyona gönderilir, kopyalama yapılmaz.

    CopyElisionExample2();  // RVO kullanılarak nesne doğrudan dönüş konumunda oluşturulur.
    CopyElisionExample3();  // NRVO ile kopyalama yapılmadan dönüş gerçekleşir.

    TemporaryMaterialization();
    TemporaryMaterialization2(Myclass{});

    ConversionConstructor();

    return 0;
}
