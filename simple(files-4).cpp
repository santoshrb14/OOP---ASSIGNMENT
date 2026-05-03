#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("file2.txt");
    string line;
    while(getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
    return 0;
}
