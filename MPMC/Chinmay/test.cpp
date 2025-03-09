#include <iostream>
using namespace std;

class B {
    int x;
public:
    B(int _x) : x(_x) { }   // Constructor initializes x
    int fun() { return x; } // Returns x
};

class D : public B {
    int y;
public:
    D(int _x, int _y) : B(_y),y(_x){}  // LINE-1
    void fun() { cout << B::fun() << y; }  // Calls fun() from B, then prints y
};

int main() {
    D *b2 = new D(1, 0);
    b2->fun();
    return 0;
}
