#include <iostream>
using namespace std;

int var = 0;  // Global variable

namespace name {
    int var = 2;  // Variable inside the namespace 'name'
}

int main() {
    int var = 1;  // Local variable inside main()

    {
        using namespace name;  // Brings namespace 'name' into scope
        cout << ::var << " " << var << " " << name::var;  // LINE-1
    }

    return 0;
}
