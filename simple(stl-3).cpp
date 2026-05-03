#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {3,1,2};
    sort(v.begin(), v.end());
    for(int x : v) cout << x;
}
