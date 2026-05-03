#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream fout("file1.txt");
    fout << "Hello File";
    fout.close();
    return 0;
}
