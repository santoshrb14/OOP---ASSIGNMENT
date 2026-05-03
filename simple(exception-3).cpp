#include <iostream>
using namespace std;

int main() {
    try {
        try {
            throw 20;
        }
        catch(int x) {
            throw;
        }
    }
    catch(int y) {
        cout << y;
    }
}
