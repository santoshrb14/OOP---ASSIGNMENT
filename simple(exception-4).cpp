#include <iostream>
#include <exception>
using namespace std;

int main() {
    try {
        throw exception();
    }
    catch(exception &e) {
        cout << "Standard Exception";
    }
}
