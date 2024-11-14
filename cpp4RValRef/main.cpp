#include <cstdint>
#include <iostream>
#include <random>

uint8_t GetRandomValue() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> dis(0, 255);
    return dis(gen);
}

void PrintRandomValue() {
    constexpr uint8_t halfByte = 127;

    // if with initializer
    if (uint8_t randomVal = GetRandomValue(); randomVal < halfByte) {
        std::cout << "Random value (" << static_cast<int>(randomVal) << ") is less than " << static_cast<int>(halfByte) << "\n\n";
    }

    else {
        std::cout << "Random value (" << static_cast<int>(randomVal) << ") is greater than or equal to " << static_cast<int>(halfByte) << "\n\n";
    }
}

void LValRefRules() {
    double dval = 3.4;
    double &r = dval;  // sol taraf degeri referansa bind olmali ve turler ayni olmali
    std::cout << "RValRefRules " << static_cast<int>(r) << '\n';

    const double &cr = 10;  // fakat const ile yapilirsa gecici nesne olusturulabilir ve sol taraf degeri sart degil
    std::cout << "RValRefRules " << static_cast<int>(cr) << '\n';

    int gn = 150;
    const double &gncr = gn;  // gncr nin scopunun sonuna kadar gn nin hayati endekslenir
    std::cout << "RValRefRules " << static_cast<int>(gncr) << "\n\n";
}

int &bar() {
    static int r = 345;
    return r;
}

int foo() { return 10; }

int baz(int &r);          // parametreye sadece L val verilebilir
int alpha(const int &r);  // parametreye R ve L val verilebilir
int beta(int &&r);        // parametreye sadece R val verilebilir

void RValRefRules() {
    int &&r = 20;  // sag taraf turunde bir degiskene sag taraf degeriyle init etmek zorunlu
    std::cout << "LValRefRules " << static_cast<int>(r) << "\n\n";

    // int &Lad = foo(); // sag taraf degeri atandigi icin sentaks hatasi
    int &Lad = bar();  // sol taraf turune sol taraf ref atanmali
    std::cout << "sol taraf turune sol taraf ref atandi " << static_cast<int>(Lad) << '\n';

    int &&Rad = foo();  // simdi sag taraf turunue sag taraf atandi okey
    std::cout << "sag taraf turune sag taraf ref atandi " << static_cast<int>(Rad) << "\n\n";
}

void TypeDeductionRules() {
    // tur cikarimi tamamen derleme zamanina ynelik bir aractir run time i yormaz
    int expr = 0;
    auto x = expr;
    auto &lx = expr;
    auto &&rx = expr;  // butun cikarimlarda farkli kurallar gecerlidir

    // auto x; ilk deger vermek gerek yoksa sentaks hatasi

    // NEDEN AUTO ?
    // kod yazmayi kolaylastirir
    // hata riski azalir

    const int cx = 10;
    auto y = cx;  // constluk duser y nin turu int olur
    y = 20;
    std::cout << "constluk dustu " << static_cast<int>(y) << '\n';

    const auto cy = cx;  // yapilmasi gerek
    // cy = 20; sentaks hatasi
    std::cout << "const auto deger degismedi " << static_cast<int>(cy) << '\n';

    int a[3] = {1, 2, 3};
    auto aa = a;  // array decay olur ve aa nin degeri a nin ilkj elemaninin degeri olur
    std::cout << "array decay auto " << static_cast<int>(*aa) << "\n\n";

    int c{700};
    auto &rc = c;
    rc = 750;
    std::cout << "referansa auto " << static_cast<int>(c) << '\n';

    const int cc{300};
    auto &crc = cc;
    // crc = 350; referans deklaratoru oldugu zaman constluk dusmez ve deger degisemez
    std::cout << "referansa auto constluk dusmedi " << static_cast<int>(cc) << '\n';

    auto &fx = foo;  // eger auto ile olmasaydi int (&fx)(); seklinde fonksiyon pointer atanacakti, islemi kisaltiyor
}

int main() {
    PrintRandomValue();
    LValRefRules();
    RValRefRules();
    TypeDeductionRules();

    return 0;
}
