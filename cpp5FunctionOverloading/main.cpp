#include <cstdint>
#include <iostream>

/*-bir dergiskenin value category si olmaz data type i olur
  -bir ifadenin value category si olur
  -isim formundaki ifadeler her zaman L valuedur
  -ifadenin turu referans olmaz normal int vs olur*/

// CONSTEXPR
constexpr int foo() { return 10; }
void ConstexprExample() {
    const int x = 10;
    constexpr int y = foo();
    int ax[x]{};
    int ay[y]{};  // y nin burada constant expression olmasi gerekiyor yoksa sentaks hatasi verir

    // bir degiskene constexpr anahtar sozcugu kullanilirsa ona ilk deger veren ifadenin sabit ifadesi olmasi gerekiyor
    // constexpr const gibi turu niteleyen bir bir sozcuk degil faakt implicitly const yapmis oluruz
}

/* FUNCTION OVERLOADING
  static binding/early binding ===> compile time
  dynamic binding/late binding ===> run time

  function overload olmasi icin;
    -fonksiyonlar ayni scopeda olacak
    -imzalari farkli olacak
        int func(int, int, int); ===>  func(int, int, int) signature tarafi*/

int foo(int);
int foo(int);  // function redecleration

int bar(int);
double bar_(int);  // sentaks hatasi ayni isim

int func(int);
int func(const int);  // function redecleration

int baz(int *p);
int baz(const int *p);  // OVERLOAD olur
int baz(int &p);
int baz(const int &p);  // OVERLOAD olur

int alpha(int *p);
int alpha(int *const p);  // function redecleration

typedef int itype;
int beta(int);
int beta(itype);  // function redecleration

// variadic fonksiyonlar en gucsuz oncelige sahip

/*exact match ===> arguman turuyle parametre turunun tam uyumu --- array-decay exact match olur
  promotion ===> terfi yukseltme
  conversion ===> tur cevirme
  exact match > promotion > conversion*/

void func(long double);
void func(char);

void omega(long);
void omega(int);
/*main()
    func(10.)  ===> double dan long doublea promotion
                    doubledan chara promotion olur bu yuzden ambiguity hatasi olur

    omega(10 > 5) ===> booldan inte promotion
                      booldan long a conversion  bu yuzden int olan daha ustun*/

void gamma(int *p);
void teta(int);
/*gamma(0) gecerli olur nullptr a conversion yapar sakincali !!
  fakat teta(nullptr); olsaydi nullptr dan inte donusum olmaz*/

void omega(int);
void omega(const int &);
/*omega(5) olsaydi her iki fonksiyona viable olur ve ambiguity olusur*/

void omega(bool);
/*int ival = 10;
  omega(&ival); pointer turunden bool turune conversion olur*/

void omega(bool);
void omega(void *);
/*int ival = 10;
  omega(&ival); void * olan kazanir her ikisi de conversion olur ama burada ozel bir durum var*/

void omega(int, int = 8);
void omega(int);
/*omega(10); ambiguity olur*/

void omega(const int &);
void omega(int &&);
/*omega(10); ikisi de viable olur fakat R val olanin digerine ustunlugu var*/

int main() {
    ConstexprExample();
    return 0;
}
