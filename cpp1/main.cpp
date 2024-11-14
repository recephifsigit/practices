#include <cstdint>
#include <iostream>

// class eklentisi isimlerin birbiriyle cakismasini onler ve implicit type
// donusumunu engeller
enum class color {
    red,
    dark,
    blue,
};

// underlying type kendimiz verebiliriz, default olarak int tanimlidir sizeof da
// 4 cikar
enum class trafficLight : uint8_t {
    red,
    green,
    black,
};

int a;          // default init
int b = 10;     // copy init
int c(10);      // direct init
double d{4.1};  // brace init, uniform init,  ayrica geri donus turu ile
                // parantez icine yazilan deger uyusmaz ise narrowing
                // conversiondan sentaks hatasi olur
int e{};        // value init bos 0 ile baslar

// :: .   bunlarin operandi olan isimlere qualified name (nitelenmis isim denir)

color myColor = color::red;
trafficLight mytrafficLight = trafficLight::black;

int main() {
    std::cout << "Hello World!\n";
    std::cout << sizeof(color) << "\n";
    std::cout << sizeof(trafficLight) << "\n";

    // implicit olarak bir enum digerine type cast edilemez class bunu koruyor
    myColor = static_cast<color>(mytrafficLight);
    std::cout << static_cast<int>(myColor) << "\n";
}