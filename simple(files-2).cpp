#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("file1.txt");
    string data;
    fin >> data;
    cout << data;
    fin.close();
    return 0;
}
