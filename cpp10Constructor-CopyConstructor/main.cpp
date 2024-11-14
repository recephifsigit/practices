#include <cstdint>
#include <iostream>

// Notlar:
// Eger sinif icinde bir constructor (ctor) tanimlanmazsa derleyici otomatik olarak kendi default ctor'unu oluşturur.
// Ancak default dişinda bir ctor tanimlandiginda, derleyici default ctor'u oluşturmaz.

// Destructor (yikici) instance.~Myclass() veya instance->~Myclass() şeklinde cagrilabilir.
// Constructor'un ana bloguna girmeden once private veya public degişkenler başlatilir.
// MIL (Member Initializer List) - veri elemanlarina ilk deger atamasi yapmak icin kullanilir.

class Myclass {
    public:
    // Member Initializer List (MIL) kullanilarak degişkenlerin ilk deger atamalari yapiliyor.
    Myclass()
        : mx(10),
          my(20)  // MIL burada ilk deger atamasi yapilir.
    {
        std::cout << "Normal ctor cagrildi.\n";
        // Kendi ekledigimiz ctor'un bir ana blogu bulunmak zorundadir.
    }

    // uc parametreli constructor
    Myclass(int x, int y, int z) : ma(x), mb(y), mc(z) {
        std::cout << "uc parametreli ctor cagrildi: "
                  << "x: " << x << " y: " << y << " z: " << z << "\n";
    }

    // Delegating constructor (C++11 ile gelmiştir)
    Myclass(int x) : Myclass(x, 0, 0) { std::cout << "Delegating ctor cagrildi: " << x << "\n"; }

    private:
    int mx;
    int my;  // MIL'deki degişken sirasi private'daki siraya uyumlu olmalidir.
             // cunku başlatma sirasi bu siraya baglidir. Aksi halde kod hata verebilir.

    // Bazi durumlarda MIL zorunludur:
    // - Sinif veri elemaninin bir referans olmasi durumunda
    // - const veri elemanlarinin ilk deger atamasi yapilmasi durumunda

    int mz{10};  // Default member initializer (C++11 ile gelmiştir)
    // int md(10); // Bu şekilde deger atamasi yapilamaz, sentaks hatasi verir

    int ma;
    int mb;
    int mc;
};

class defaultSentaksError {
    public:
    defaultSentaksError();  // ; eklenirse user-defined ctor olur, {} eklenirse default ctor olur

    // default anahtar kelimesi special member functionlara ozeldir
    // delete herhangi bir fonksiyonda kullanilabilir

    // Eger derleyici sinifin bir ozel uye fonksiyonunu default edecekse fakat bu surecte bir hata olursa derleyici bu fonksiyonu delete eder
    private:
    const int x = 0;  // const degerler ilk deger atamasi olmadan başlatilamaz
};

void DelegatingAndNormalCtor() {
    Myclass();            // Default ctor cagirir
    Myclass(40);          // Delegating ctor cagirir, once uc parametreli ctor'u cagirir, ardindan delegating ctor'u cagirir
    Myclass(50, 60, 70);  // uc parametreli ctor'u cagirir
}

void DefaultSentaksErrorExample() {
    // defaultSentaksError mx; // Const bir nesne deger almadan init edildigi icin deleted fonksiyon cagri hatasi olur
}

class CopyCtor {
    public:
    // Copy constructor - parametik yapisi
    CopyCtor() {};
    CopyCtor(const CopyCtor& other) { std::cout << "Copy ctor cagrildi.\n"; }

    // Derleyicinin yazdigi copy ctor
    // CopyCtor(const CopyCtor& other) : ax(other.ax), ay(other.ay), az(other.az) { std::cout << "Copy ctor cagrildi.\n"; }

    private:
    int ax = 0;
    int ay = 0;
    int az = 0;
};

void func(CopyCtor m) {}
CopyCtor foo() { return CopyCtor(); }

void CopyCtorExample() {
    CopyCtor m1;
    CopyCtor m2(m1);      // Copy ctor cagirir
    CopyCtor m3{m2};      // Copy ctor cagirir
    CopyCtor m4 = m3;     // Copy ctor cagirir
    CopyCtor m5 = foo();  // Copy ctor cagirir
    func(m1);             // Copy ctor cagirir
}

int main() {
    DelegatingAndNormalCtor();
    DefaultSentaksErrorExample();
    CopyCtorExample();
}
