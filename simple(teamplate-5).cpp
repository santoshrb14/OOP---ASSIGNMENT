#include <iostream>
using namespace std;

template <typename T>
void printArr(T arr[], int n) {
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
}

int main() {
    int arr[] = {1,2,3,4};
    printArr(arr, 4);
    return 0;
}
