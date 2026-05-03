#include <iostream>
using namespace std;

template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

template <>
char maximum<char>(char a, char b) {
    cout << "Char specialization\n";
    return (a > b) ? a : b;
}

int main() {
    cout << maximum('a', 'z');
    return 0;
}
