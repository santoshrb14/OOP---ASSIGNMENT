#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("file1.txt");
    string line;
    int count = 0;

    while(getline(fin, line)) {
        count++;
    }

    cout << "Lines: " << count;
    fin.close();
    return 0;
}
