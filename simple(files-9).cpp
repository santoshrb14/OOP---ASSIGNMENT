#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream fout("num.txt");
    fout << 10 << " " << 20 << " " << 30;
    fout.close();

    ifstream fin("num.txt");
    int x;
    while(fin >> x) {
        cout << x << " ";
    }

    fin.close();
    return 0;
}
