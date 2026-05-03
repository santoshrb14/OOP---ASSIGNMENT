#include <iostream>
using namespace std;

template <typename T1, typename T2>
void show(T1 a, T2 b) {
    cout << a << " " << b;
}

int main() {
    show(10, 2.5);
    return 0;
}
