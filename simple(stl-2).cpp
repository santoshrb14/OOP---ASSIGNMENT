#include <iostream>
#include <map>
using namespace std;

int main() {
    map<int,string> m;
    m[1] = "One";
    m[2] = "Two";
    cout << m[1];
}
