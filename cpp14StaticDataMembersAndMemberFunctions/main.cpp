#include <cstdint>
#include <iostream>

// Static veri elemanları sınıfın veri elemanlarıdır, nesneye (instance) ait değildir.
// Her yeni nesne oluşturulduğunda static veri elemanları tekrar oluşturulmaz.
// Static veri elemanları sınıfın parçasıdır, ancak sınıfın boyutunu etkilemez.
// Sınıfın bir nesnesi (objesi) olmadan da static veri elemanlarına erişilebilir.
// Her nesne oluşturulduğunda non-static veri elemanları için ayrı bir hafıza alanı ayrılır.

class Myclass {
    public:
    Myclass() {}  // MIL'de (Member Initializer List) static elemanlar başlatılamaz.
                  // `Myclass() : x{10} {}` yazılamaz, sentaks hatası olur.

    int mx;                    // Non-static veri elemanı, her nesne için ayrı bir alan ayrılır.
    static int x;              // Sadece bildirim, tanımlama dışarıda yapılır.
    static const int y = 20;   // Sabit static veri elemanları sınıf içinde tanımlanabilir.
    static inline int z = 40;  // `inline` anahtar kelimesiyle sınıf içinde tanımlanabilir.

    int func() { return x; }  // Non-static fonksiyonlar static veri elemanlarına erişebilir.

    int funcConst() const {
        x = 746;
        return x;
    }  // Non-static `const` fonksiyonlar static elemanlara erişebilir ve değiştirebilir.

    static int sbar() {
        // Static üye fonksiyonlar gizli `this` nesnesine erişim sağlamaz, dolayısıyla instance'a ait değil, sınıfa aittir.
        // Non-static veri elemanlarına veya non-static üye fonksiyonlara erişemezler.
        // func();  // Non-static fonksiyonlara erişmeye çalışmak sentaks hatasıdır.
        return x + 1000;
    }

    static int sreturnDeger() { return 1000; }

    // static int barConst() const { return x + 1000; }; // Static fonksiyonlar `const` olamaz, çünkü `this` gizli parametresini alamaz.
};

int sreturnDeger() { return 1000; }  // Global returnDeger fonksiyonu

// Static veri elemanının tanımlanması (Sınıf dışında yapılmalıdır).
// Programın link edilebilmesi için static veri elemanının tanımı gereklidir.
// İlk değer ifadesi önce sınıf içinde, sonra globalde aranır. Overloading geçerli değildir.
int Myclass::x = sreturnDeger() + ::sreturnDeger();

int main() {
    std::cout << Myclass::x << std::endl;  // Static veri elemanı doğrudan sınıf ismiyle erişilebilir.
    Myclass::x = Myclass::y;               // Sınıf içindeki static const değişkene erişim
    std::cout << Myclass::x << std::endl;
    Myclass::x = Myclass::z;  // Sınıf içindeki static inline değişkene erişim
    std::cout << Myclass::x << std::endl;

    Myclass y;                                      // Yeni bir nesne
    std::cout << y.func() + 100 << std::endl;       // Non-static fonksiyon üzerinden static değişkene erişim
    std::cout << y.funcConst() + 200 << std::endl;  // Non-static const fonksiyon üzerinden static değişkene erişim
    std::cout << Myclass::sbar() << std::endl;      // Static fonksiyon doğrudan sınıf ismiyle çağrılır
    y.func();
    y.sbar();  // Static fonksiyon doğrudan sınıf ismiyle çağirilabilir, ancak nesne üzerinden de çağrılabilir.

    return 0;
}
