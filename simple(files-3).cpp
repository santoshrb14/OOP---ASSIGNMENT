#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream fout("file2.txt");
    fout << "Line1\nLine2\nLine3";
    fout.close();
    return 0;
}
