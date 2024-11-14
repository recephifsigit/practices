#include <cstdint>
#include <iostream>

// INLINE EXPANSION
// - Eger bir fonksiyon tanimini header dosyasina koyacaksak, inline olarak tanimlamak gerekiyor.
// - Bu sekilde ONE DEFINITION RULE (ODR) ihlal edilmez.
// - Inline olarak bildirilse bile derleyici bu istege uyup uymamakta ozgurdur.
// - Farkli kaynak dosyalarda fonksiyonun token-by-token ayni olmasi gerekir.
// - Eger bir header dosyasinda tum fonksiyonlar inline tanimlanmissa, .cpp dosyasina ihtiyac duymayan bir modul olusturulabilir, buna header-only-library denir.
// - Dezavantajlari: Derleme suresi uzayabilir, gizlilik ihlali olabilir.
// - Inline degiskenler de olusturulabilir, farkli cpp dosyalarinda cagrilsa bile hata vermez.
// - Siniflarin uye fonksiyonlari da inline olabilir; tanimda veya deklarasyonda en az birinde inline anahtar kelimesi olmalidir.
// - Ancak, sinif icinde tanimlanan bir fonksiyon dolayli olarak inline olur.

extern "C" void foo();  // C++ derleyicisine, C fonksiyonu oldugunu belirtir.

extern "C" {
void bar();
void baz();  // Ayni blokta birden fazla fonksiyon tanimlanabilir.
}

// CONSTRUCTORS & SPECIAL MEMBER FUNCTIONS
// - Constructor fonksiyonlar sinif ismi ile ayni olmali ve donus degeri olmamalidir.
// - Parametre alabilir ve overload edilebilir.
// - Asagidaki durumlarda compiler kendi default fonksiyonlarini olusturur:
//   1) Default constructor
//   2) Copy constructor
//   3) Copy assignment operator
//   4) Move constructor
//   5) Move assignment operator
//   6) Destructor
// - Derleyicinin otomatik olusturdugu fonksiyonlar, belirli durumlarda sinifin ozel ihtiyaclarina uygun olmayabilir.

class Myclass {
    public:
    Myclass() { std::cout << "Myclass Default ctor cagrildi\n"; }
    ~Myclass() { std::cout << "Myclass Destructor cagrildi\n"; }
};

// Automatic Class Instance ornegi icin Myclass
void AutomaticClassInstanceExampleMyclass() {
    Myclass m;  // Bu fonksiyon cagrildiginda m nesnesi olusturulur ve fonksiyon sonunda yok edilir.
}

class Rec {
    public:
    Rec() { std::cout << "Rec Default ctor cagrildi\n"; }
    Rec(int x) { std::cout << "Rec int Parametreli ctor cagrildi\n"; }
    ~Rec() { std::cout << "Rec Destructor cagrildi\n"; }
};

// Automatic Class Instance ornegi icin Rec sinifi
void AutomaticClassInstanceExampleRec() {
    Rec ar[5];  // Bu fonksiyon cagrildiginda 5 adet Rec nesnesi olusturulur ve fonksiyon sonunda yok edilir.
}

void AutomaticClassInstanceExampleParameterConstructor() {
    Rec ar = 10;
    Rec ar2(10);
    Rec ar3{10};  // Bu sekilde deger atayarak parametreli ctor cagrilir.
}

// STATIC INITIALIZATION FIASCO
// - Statik bir degiskenin baslatilmasinin, baska bir statik degiskene bagimli olmasi durumunda ortaya cikar.
// - Baslatma sirasi garanti edilmediginden, bagimli olan degisken baslatilmamis olabilir ve bu programin beklenmedik sekilde davranmasina yol acabilir.

int main() {
    AutomaticClassInstanceExampleMyclass();
    AutomaticClassInstanceExampleRec();
    AutomaticClassInstanceExampleParameterConstructor();
    return 0;
}
