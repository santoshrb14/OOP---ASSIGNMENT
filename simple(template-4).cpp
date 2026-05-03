#include <iostream>
using namespace std;

template <typename T>
void increment(T &x) {
    x++;
}

int main() {
    int a = 5;
    increment(a);
    cout << a;
    return 0;
}
