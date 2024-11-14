#include <cstdint>
#include <iostream>

class Myclass {
    public:
    Myclass() {}  // Varsayılan yapıcı fonksiyon (constructor)

    // Myclass();  // Bu şekilde sadece bildirirsek, tanımlı bir default constructor olmadığı için derleyici hata verir: "no appropriate default constructor available"

    ~Myclass() {}  // Yıkıcı fonksiyon (destructor) bildirildiğinde, derleyici default copy constructor ve copy assignment operator'ü sağlar.
                   // Ancak move constructor ve move assignment operator için herhangi bir varsayılan sağlanmaz, bunları manuel olarak tanımlamak gerekir.

    // Eğer aşağıdaki gibi yıkıcı, copy constructor veya copy assignment operator manuel olarak tanımlanırsa,
    // sınıfın move constructor ve move assignment member'ları da default olarak sağlanmaz:
    // ~Myclass() {}
    // Myclass(const Myclass& other) {}
    // Myclass& operator=(const Myclass& other) {}
    // Bu durumda, move işlemleri için de manuel tanımlamalar yapmak gerekir.

    Myclass(Myclass&& other) {}                            // Eğer move constructor tanımlanırsa, derleyici artık copy constructor sağlamaz (delete eder).
    Myclass& operator=(Myclass&& other) { return *this; }  // Move assignment operator

    // Özetle:
    // - Destructor tanımlanırsa, derleyici copy işlemleri varsayılan olarak sağlar.
    // - Copy işlemlerinden biri tanımlanırsa, derleyici move işlemlerini sağlamaz.
    // - Move işlemlerinden biri tanımlanırsa, derleyici copy işlemlerini sağlamaz (delete eder).
};

// Dinamik Ömürlü Nesne Örneği
void DinamicOmurluNesneExample() {
    Myclass* m = new Myclass;  // Myclass tipinde dinamik bir nesne oluşturur ve adresi bir pointera atar.
    Myclass* p{new Myclass};   // Diğer bir dinamik nesne oluşturma örneği
    delete m, p;               // p ve m nesnelerinin yaşam döngüsünü sonlandırır, belleği serbest bırakır.

    class Rec {
        public:
        Rec() { std::cout << "Rec address:     " << this << "\n"; }
    };

    Rec* r = new Rec;                               // `new` operatörü `Rec` sınıfı kadar bellek ayırır ve yapıcı fonksiyonu çağırır.
                                                    // Hata durumunda `new` operatörü `malloc` gibi `nullptr` döndürmez, bir exception throw eder.
                                                    // `malloc` belleği başlatmadan `nullptr` döndürürken, `new` ile belleğin başlatılması garanti edilir.
    std::cout << "instance address:" << r << "\n";  // Nesnenin `this` pointer adresi ile aynı adresi gösterir.
    delete r;                                       // `r` nesnesi silinmezse destructor çağrılmaz ve bellek kaynağı geri verilmez.
}

int main() {
    Myclass m;                    // Otomatik ömürlü nesne örneği
    DinamicOmurluNesneExample();  // Dinamik ömürlü nesne örneğini çağır
    return 0;
}
