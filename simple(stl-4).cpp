#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {1,2,3};
    auto it = find(v.begin(), v.end(), 2);
    if(it != v.end()) cout << "Found";
}
