#include <cstdint>
#include <iostream>

class incompleteClass;  // class declaration, incomplete type

class Myclass {
    // sinifin ana blogu icinde tanimlanan varliklara sinifin memberlari denir
};

/* CLASS MEMBER TURLERI:
   empty class,
   data member     ===> int mx;
   member function ===> int foo(){}
   type member     ===> nested type, typedef vs..
*/

// static olmayan (non-static) veri elemanlari her instance da yer kaplarlar
// fakat static veri elemanlari instancenin degil sinifin genel elemanidir
// instancenin sizeini etkilemez

/* sinif elemanlarina erisim sentaks sirasi:
    name lookup
        context control
            access control

*/

// public:    disariya acik alan
// private:   sadece sinifin kendisine ait alan, memberlar kullanabilir
// protected: kalitimdan elde edilmis siniflar kullanabilir

class Example {
    public:
    int foo() { return func(); }  // private deki fonksiyon burada cagirilabilir

    private:
    int func() { return 100; }  // 100 degeri doner
};

// global fonksiyonlarin bildirimleri birden fazla kez yapilabilir
// fakat class icinde fonksiyon bildirimi sadece bir kere yapilabilir

int main() {
    incompleteClass* pointerVar;  // bununla bir pinter degisken tanimlanabilir
    // Myclass nonPointerVar; // ama pointer olmayan degisken tanimlanamaz sentaks
    // hatasi

    Example m;
    auto f1 = m.foo();  // bu erisebilir cunku public
    // m.func();  // bu erisemez cunku private alanda

    std::cout << "foo(): " << f1;  // public fonksiyon cagirdik o da privatedeki fonksiyonu cagirdi

    return 0;
}
