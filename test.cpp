#include <iostream>
using namespace std;

static int i = 5;  // Global static variable `i`

class myClass {
public:
    myClass() { cout << ++i; }   // Constructor: Pre-increments `i` and prints it
    ~myClass() { cout << i--; }  // Destructor: Prints `i` and then post-decrements it
};

void check(myClass c) {  
    // Function that takes an object by value (causing copy constructor & destructor to be called)
}

int main() {
    myClass c1;  // Creates an object of `myClass`
    check(c1);   // Passes the object to the function `check`
    return 0;
}
