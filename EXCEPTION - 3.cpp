#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class HistoryStack {
private:
    T*   data;
    int  topIndex;
    int  capacity;

public:
    HistoryStack(int cap = 10) : topIndex(-1), capacity(cap) {
        data = new T[capacity];
    }

    ~HistoryStack() { delete[] data; }

    void push(const T& item) {
        if (topIndex == capacity - 1)
            throw overflow_error("History stack full!");
        data[++topIndex] = item;
    }

    T pop() {
        if (isEmpty())
            throw underflow_error("No history to go back to!");
        return data[topIndex--];
    }

    T peek() const {
        if (isEmpty()) throw underflow_error("Stack is empty!");
        return data[topIndex];
    }

    bool isEmpty() const { return topIndex == -1; }
    int  size()    const { return topIndex + 1; }

    void showAll() const {
        cout << "History (top -> bottom): ";
        for (int i = topIndex; i >= 0; i--)
            cout << data[i] << (i > 0 ? " <- " : "");
        cout << endl;
    }
};

int main() {
    // --- Browser History ---
    cout << "=== Browser History Demo ===" << endl;
    HistoryStack<string> browser;
    browser.push("google.com");
    browser.push("stackoverflow.com");
    browser.push("cppreference.com");
    browser.showAll();
    cout << "Current page : " << browser.peek() << endl;
    cout << "Going back to: " << browser.pop() << endl;
    cout << "Now on       : " << browser.peek() << endl;

    // --- Undo System for a text editor (int represents state IDs) ---
    cout << "\n=== Text Editor Undo Demo ===" << endl;
    HistoryStack<int> undoStack;
    for (int i = 1; i <= 5; i++) {
        undoStack.push(i * 10);   // state snapshots: 10,20,30,40,50
        cout << "Saved state: " << i * 10 << endl;
    }
    cout << "Undoing last 2 actions..." << endl;
    cout << "Reverted: " << undoStack.pop() << endl;
    cout << "Reverted: " << undoStack.pop() << endl;
    cout << "Current state: " << undoStack.peek() << endl;

    return 0;
}
