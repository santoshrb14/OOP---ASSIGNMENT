#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("file1.txt");
    string word;
    int count = 0;

    while(fin >> word) {
        count++;
    }

    cout << "Words: " << count;
    fin.close();
    return 0;
}
