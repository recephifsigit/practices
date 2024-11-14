#include <cstdint>
#include <iostream>

// varsayilan arguman derleme zamanina iliskin islemdir
// hem bilidirimde hem fonksiyon taniminda kullanilirsa sentaks hatasi olur
// header da bir bildirim varsa ona ek olarak varsayilan argumanli bir bildirim yapilabilir
// hazir fonksiyon parametrelerini kendi istegimize gore kullanmak istersek wrapper yazilabilir

// default arguman parametrelerde kullanilabilir
// fonksiyon geri donus degeri default argument olarak da kullanilabilir
int foo(int = 5, int = 9);
void func(int a, int = foo());

// burada fonksiyon bildirimine default deger verildi o basilacak eger parametre
// girilmezse

int defArgFunc(int = 10);
int defArgFunc(int a) { return a; }

void nullExample(int *p = nullptr);  // parametre girilmedigi takdirde nullptr basilacak
void nullExample(int *p) { std::cout << "parameter address val: " << p << "\n"; }

int main() {
    // eger parametreye deger girilmezse dewfault olarak fonksiyon bildirimindeki
    // deger yazilacak

    std::cout << "input value: " << defArgFunc() << "\n";
    std::cout << "input value: " << defArgFunc() << "\n";
    std::cout << "input value: " << defArgFunc(200) << "\n\n";

    // eger deger girlmezse default olarak nullptr olacaktir
    nullExample();
    int x;
    nullExample(&x);
}