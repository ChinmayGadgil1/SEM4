#include <iostream>
#include <string>
using namespace std;

template <typename T, int n> // LINE-1
class MultiPrint {
    T val;
public:
    MultiPrint(T _val) : val(_val) {}
    void output() {
        for (int i = 0; i < n; i++)
            cout << val << " ";
    }
};

int main() {
    int n = 3; // n declared as a constant
    MultiPrint<string, n> d("hello"); // LINE-2
    d.output();
    return 0;
}
