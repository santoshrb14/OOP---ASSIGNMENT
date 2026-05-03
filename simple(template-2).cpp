#include <iostream>
using namespace std;

template <typename T = int>
T square(T x) {
    return x * x;
}

int main() {
    cout << square(5);
    return 0;
}
