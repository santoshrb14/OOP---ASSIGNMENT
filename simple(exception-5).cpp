#include <iostream>
using namespace std;

int main() {
    int arr[3] = {1,2,3};
    try {
        throw "Out of bounds";
    }
    catch(const char* msg) {
        cout << msg;
    }
}
