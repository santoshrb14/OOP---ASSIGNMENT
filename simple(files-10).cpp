#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("nofile.txt");

    if(!fin) {
        cout << "File not found";
    } else {
        cout << "File opened";
    }

    return 0;
}
