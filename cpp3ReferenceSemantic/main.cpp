#include <iostream>

int x{10};
int &y = x;  // referanslar default initialize edilemez
// y x'e scopeu boyunca baglandigi nesneye bagli kalir

int *p1 = &y;
int *p2 = &x;  // ayni anlama gelir

int &r1 = x;
int &r2 = (x);
int &r3 = {x};  // bu sekillerde ilk deger verilebilir

// ! bir L value referansa bir L value expression ile deger verebiliriz
// eger & operandinin operandi yapilirsa bir degisken ve sentaks hatasi olmazasa
// o deger L value dur

// PRIMARY VALUE CATEGORIES
// PR value - pure R value
// L value - expression
// X value - expiring value

void incrementReference() {
    ++x;
    ++y;  // usttekiyle alttaki islem aynidir sonuc 12 olur
    std::cout << x << "\n\r";
}

void arrayReference() {
    int a[5] = {1, 2, 3, 4, 5};
    int(&r)[5] = a;  // burada diziyi referans alabiliriz
    std::cout << r[0] << "\n\r";
}

int g = 10;
int &func() { return g; }

void functionReference() {
    std::cout << g << "\n\r";
    int &a = func();  // burada fonksiyon global bir degiskene referans oldu sonra onu
                      // da baska bir referensa baglayinca g yi degistirebildik
    a = 999;
    std::cout << g << "\n\r";
}

int main() {
    incrementReference();
    arrayReference();
    functionReference();
}