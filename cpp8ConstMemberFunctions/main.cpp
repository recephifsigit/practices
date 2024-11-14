#include <cstdint>
#include <iostream>

/**
 * @class Myclass
 * @brief Demonstrates const member functions, const overloads, mutable members, and function chaining.
 *        class icinde tanimlanan fonksiyonlar inlinedir
 *        member function icinde unqualified name ile cagirilirsa once fonksiyon icine sonra globale sonra class icinde arar
 */
class Myclass {
    public:
    /**
     * @brief Const member function, cannot modify members.
     *        gizli parametre (Myclass *) dan (const Myclass *) ' e donusur
     */
    void func() const {}

    /**
     * @brief Modifies the non-const member variable m_x.
     */
    void foo() { m_x = 10; }

    /**
     * @brief Prints a message for const overload.
     */
    void bar() const { std::cout << "const cagirildi\n"; }

    /**
     * @brief Prints a message for non-const overload.
     */
    void bar() { std::cout << "non-const cagirildi\n"; }

    /**
     * @brief Prints and increments the mutable member variable.
     */
    void printMutable() const { std::cout << "mutable member: " << ++print << "\n"; }

    /**
     * @brief Returns a reference to the object itself.
     * @return Reference to *this.
     */
    Myclass& returnItselfA() {
        std::cout << "returnItselfA cagirildi\n";
        return *this;
    }

    /**
     * @brief Returns a reference to the object itself.
     * @return Reference to *this.
     */
    Myclass& returnItselfB() {
        std::cout << "returnItselfB cagirildi\n";
        return *this;
    }

    /**
     * @brief Returns a reference to the object itself.
     * @return Reference to *this.
     */
    Myclass& returnItselfC() {
        std::cout << "returnItselfC cagirildi\n";
        return *this;
    }

    private:
    int m_x = 0;             /**< Non-const member variable. */
    mutable int print = 199; /**< Mutable member, can be modified in const functions. */
};

/**
 * @brief Example function demonstrating const member functions.
 */
void ConstMemberFuncExample() {
    const Myclass x;
    x.func();
    Myclass y;
    y.foo();
}

/**
 * @brief Example function demonstrating const and non-const overloads.
 */
void ConstOverloadExample() {
    const Myclass a;
    a.bar();
    Myclass b;
    b.bar();
}

/**
 * @brief Example function demonstrating mutable members.
 */
void MutableMemberExample() {
    Myclass a;
    a.printMutable();
}

/**
 * @brief Example function demonstrating function chaining.
 */
void ReturnItselfExample() {
    Myclass a;
    a.returnItselfA().returnItselfB().returnItselfC();
}

int main() {
    ConstMemberFuncExample();
    ConstOverloadExample();
    MutableMemberExample();
    ReturnItselfExample();
    return 0;
}
