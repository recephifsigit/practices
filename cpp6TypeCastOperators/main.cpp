#include <cstdint>
#include <iostream>

void Func(const double&) { std::cout << "L value cagirildi\n"; }

void Func(double&&) { std::cout << "R value cagirildi\n"; }

/*  TUR DONUSTURME OPERATORLERI:
    static_cast
    dynamic_cast
    reinterpret_cast
    const_cast
*/

enum class Color { red, green, blue };
enum class Family { dad = 10, mom, child };

void UsingExample() {
    using enum Color;
    auto c1 = red;  // using kullanarak tur ismi eklemeyebiliriz
    std::cout << "color:  " << static_cast<int>(c1) << "\n";

    using Family::dad;
    auto f1 = dad;  // ya da daha spesifik enum elemani kullanabiliriz
    std::cout << "family: " << static_cast<int>(f1) << "\n";
}

int main() {
    const double x = 10;

    Func(x);
    Func((double)x);  // tur donusturme operatoruyle olusturulan bir ifade hedef
                      // tur referans turu degilse PR value expressiondur

    UsingExample();
    return 0;
}
