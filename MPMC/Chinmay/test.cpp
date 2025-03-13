#include <iostream>
using namespace std;

class B {
    int a;
public:
    B(int x) : a(x) {}
    int get() { return a; }
    void set(int x) { a = x + 1; }
};

class D : public B {
    int b;
public:
    D(int x, int y) : B(x), b(y) {}

    void change(int c) {
        static_cast<B&>(*this).set(c); // Accessing base class function
        b = c + 1;
    }

    void print() {
        cout << B::get() << " " << b;
    }
};

int main() {
    D d(10, 20);
    d.change(7);
    d.print();
    return 0;
}
