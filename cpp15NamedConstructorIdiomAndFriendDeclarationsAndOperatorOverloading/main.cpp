#include <iostream>

// Named Constructor Idiom örneği
void NamedConstructorIdiom() {
    /*
    Named Constructor Idiom (Adlandırılmış Yapıcı Yöntemi), C++'da sınıf nesnelerini oluştururken
    özel olarak adlandırılmış fabrika metotları kullanarak yapıcıları gizlemeye yönelik bir tekniktir.
    Bu teknik, özellikle aynı türde birden fazla yapıcı tanımlamak veya yapıcıların kullanımını
    daha anlaşılır hale getirmek istediğimizde faydalıdır.
    */

    class Myclass {
        public:
        // İki sayıyı toplayan named constructor
        static Myclass ReturnSum(int x, int y) { return Myclass(x + y); }

        // Sonucu yazdırmak için bir metot
        void print() const { std::cout << "Toplam: " << x << std::endl; }

        private:
        // Tek bir parametre alan yapıcı
        Myclass(int result) : x{result} {}

        int x;  // Toplam sonucu tutmak için
    };

    // İki sayının toplamını almak ve sonucu yazdırmak
    Myclass result = Myclass::ReturnSum(5, 10);
    result.print();
}

// friend bildirimi örneği
class nonCompleteTypeClass;  // Tamamlanmamış tip bildirimi

class myClass2 {
    public:
    private:
};

class Rec {
    public:
    // friend bildirimi: Serbest fonksiyon, başka bir sınıf ve tüm üye fonksiyonlar için
    friend void gFriendFunc();
    friend myClass2;

    private:
    int mx, my;
    int foo() { return 0; }
};

void gFriendFunc() {
    Rec r;
    std::cout << "gFriendFunc(): " << r.foo() << std::endl;
}

// Operatör aşırı yükleme örnekleri
enum class Color { RED, GREEN, BLUE };
enum class Fruit { BANANA, APPLE, CHERRY };

class ArityClass {
    public:
    explicit ArityClass(int x) : value(x) {}

    // Üye fonksiyon olarak bölme operatörü
    int operator/(const ArityClass& other) const {
        if (other.value == 0) {
            std::cerr << "Error: Division by zero!" << std::endl;
            return 0;
        }
        return value / other.value;
    }

    // Unary negation operator (!)
    bool operator!() const { return (value % 2 == 0); }

    // Fonksiyon çağrısı operatörü
    int operator()(Color x) { return static_cast<int>(x); }

    // Atama operatörü
    ArityClass& operator=(const char* string) {
        std::cout << string << "\n";
        return *this;
    }

    private:
    int value;
};

// Non-member operatör aşırı yükleme fonksiyonları
int operator*(ArityClass lhs, ArityClass rhs) {
    return 0;  // Gerekli şekilde uygulanabilir
}

int operator*(Color a, Fruit b) { return static_cast<int>(a) * static_cast<int>(b); }
int operator*(Color a, int b) { return static_cast<int>(a) * b; }
int operator*(int a, Color b) { return a * static_cast<int>(b); }
int operator+(Color a, Fruit b) { return static_cast<int>(a) + static_cast<int>(b); }

// Fonksiyonlar
void DivideOperatorOverLoad() {
    ArityClass a{15}, b{5};
    int z = a / b;  // a.operator/(b) çağrılır
    std::cout << "DivideOperatorOverLoad(): " << z << std::endl;
}

void NotOperatorOverLoad() {
    ArityClass a{15};
    bool ac = a.operator!();  // a.operator!() çağrılır
    std::cout << "NotOperatorOverLoad(): " << ac << std::endl;
}

void MultiplyOperatorOverLoad() {
    std::cout << "Color::GREEN * Fruit::CHERRY: " << Color::GREEN * Fruit::CHERRY << std::endl;
    std::cout << "Color::GREEN * 4: " << Color::GREEN * 4 << std::endl;
    std::cout << "4 * Color::BLUE: " << 4 * Color::BLUE << std::endl;
}

void SumOperatorOverLoad() {
    auto a = Color::BLUE;
    auto b = Fruit::CHERRY;
    int z = a + b;  // a.operator+(b) çağrılır
    std::cout << "SumOperatorOverLoad(): " << z << std::endl;
}

void FunctionCallOperatorOverLoad() {
    ArityClass instance(10);
    auto a = instance(Color::BLUE);  // instance.operator()(Color::BLUE) çağrılır
    std::cout << "FunctionCallOperatorOverLoad(): " << a << std::endl;
}

void AssignOperatorOverLoad() {
    ArityClass instance(10);
    instance = "Hello, World!";  // instance.operator=("Hello, World!") çağrılır
}

// main fonksiyonu
int main() {
    NamedConstructorIdiom();
    gFriendFunc();
    DivideOperatorOverLoad();
    MultiplyOperatorOverLoad();
    NotOperatorOverLoad();
    SumOperatorOverLoad();
    FunctionCallOperatorOverLoad();
    AssignOperatorOverLoad();

    std::cout << "recep" << std::endl;           // biri yazi bastirir
    std::cout.operator<<("recep") << std::endl;  // bu adresi bastirir
    return 0;
}
