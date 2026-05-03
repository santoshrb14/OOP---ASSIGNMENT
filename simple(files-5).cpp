#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream fout("file1.txt", ios::app);
    fout << "\nAppended Text";
    fout.close();
    return 0;
}
