#include <cstdint>
#include <iostream>

// Eger bir sinif nesnesine ayni turden baska bir sinif nesnesi "=" operatoruyle atanirsa,
// COPY ASSIGNMENT ozel uye fonksiyonu devreye girer.
// ornegin, x = y yapildiginda her iki nesne de varligini korur (hayattadir).

// PARAMETRIK YAPI:
// Myclass& operator=(const Myclass & other);
// a = b durumunda, copy assignment `a` icin cagrilacak, `b` ise fonksiyona arguman olarak gececektir.

void ConstructorExamples() {
    class Myclass {
        public:
        Myclass() { std::cout << "default constructor cagirildi\n"; }
        Myclass(const Myclass& other) { std::cout << "copy constructor cagirildi\n"; }
        Myclass& operator=(const Myclass& other) {
            if (this != &other)  // Self-assignment kontrolu
            {
                ax = other.ax;
                bx = other.bx;
                cx = other.cx;
                std::cout << "copy assignment: self assignment degil\n";
            } else {
                std::cout << "copy assignment: self assignment\n";
            }
            return *this;
        }

        Myclass(Myclass&& other) : ax{std::move(other.ax)}, bx{std::move(other.bx)}, cx{std::move(other.cx)} { std::cout << "move constructor cagirildi\n"; }  // derleyicinin yazidigi move ctor

        Myclass& operator=(Myclass&& other)  // derleyicinin yazidigi move assignment
        {
            if (this != &other)  // Self-assignment kontrolu
            {
                ax = std::move(other.ax);
                bx = std::move(other.bx);
                cx = std::move(other.cx);
                std::cout << "move assignment: self assignment degil\n";
            } else {
                std::cout << "move assignment: self assignment\n";
            }
            return *this;
        }

        void foo(Myclass&& r) {
            std::cout << "fonsiyonda move constructor cagirildi\n";
            Myclass x = r;             // boyle olunca yine move ctor cagirilmaz cunku r hala isim formunda, R value ye cevirilmesi lazim, "copy constructor cagirildi" yazisi cikar
            Myclass u = std::move(r);  // ayni buradaki gibi move edilir    "move constructor cagirildi" yazisi cikar
        }

        private:
        int ax{}, bx{}, cx{};
    };

    Myclass a, b, c, d, e, f, g, h;         // Default constructor cagrilir
    a = a;                                  // Self-assignment, copy assignment cagrilir
    a = b = c = d = e = f = g = h;          // "fluent API" ornegi. `Myclass&` donduruldugu icin L-value olusturulabilir.
    b = a;                                  // copy assignment cagrilir
    Myclass cCtor = a;                      // İlk atamada copy constructor cagrilir
    Myclass x;                              // Default constructor cagrilir
    Myclass y = static_cast<Myclass&&>(x);  // Move constructor cagrilir
    Myclass k = std::move(x);               // Move constructor cagrilir
    Myclass l, j;                           // Default constructor cagrilir
    l = std::move(j);                       // move assignment cagrilir
    j = std::move(j);                       // self-assignment move assignment cagrilir
    a.foo(std::move(b));                    // move constructor cagrilir, hatta burada "a.foo(b);" yazarsak L valueyi R ye bind etme hatasi verir
}

// C++'da atama operatoruyle olusturulan ifadelerin deger kategorileri L-value’dir.
// Eger copy assignment operator fonksiyonunu kendimiz yaziyorsak, self-assignment kontrolu eklememiz onerilir.
// if(this == &other) return *this;

// Buyuk uclu: copy constructor, copy assignment, destructor.
// Eger bunlardan biri tanimlanirsa, digerlerinin de tanimlanmasi onerilir.
// Derleyiciye birakmak, yonetimsel sorunlara yol acabilir.

// TASIMA SEMANTIGI
// C++11 ile birlikte, copy constructor ve copy assignment yerine move constructor ve move assignment tanimlanabilir.
// Move constructor ve move assignment, kaynak nesnenin icerigini tasiyarak hedef nesneye aktarir.
// std::string str(20000, 'A');
// std::string s{str}; boyle olursa copy constructor cagrilir ve cok fazla maliyetlidir ameleliktir.
// Myclass x = baska_nesne;  eger kodun kaynagi geri verilecekse destruct olmadan diger nesneye atama yapilarak kaynak x e aktarilabilir.
// ama baska_nesne baska yerlerde hala kullanimdaysa ortalik karisir. baska_nesne nin hayatinin bitip bitmemesine yonelik ya kaynak copy edilir ya da move edilir.
// eger bir ifade R val ve sinif turunden ise onun kaynagi move edilebilir baska yerde kullanilma ihtimali yok demektir guvenlidir.

int main() {
    ConstructorExamples();
    return 0;
}
