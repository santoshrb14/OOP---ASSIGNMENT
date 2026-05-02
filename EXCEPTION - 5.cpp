#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T, typename Comparator>
class PriorityQueue {
private:
    T* heap;
    int size;
    int capacity;
    Comparator  cmp;       // custom comparator: returns true if a has higher priority

    void siftUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (cmp(heap[i], heap[parent])) { swap(heap[i], heap[parent]); i = parent; }
            else break;
        }
    }

    void siftDown(int i) {
        while (2 * i + 1 < size) {
            int left = 2*i+1, right = 2*i+2, best = i;
            if (left  < size && cmp(heap[left],  heap[best])) best = left;
            if (right < size && cmp(heap[right], heap[best])) best = right;
            if (best == i) break;
            swap(heap[i], heap[best]); i = best;
        }
    }

public:
    PriorityQueue(int cap, Comparator c) : size(0), capacity(cap), cmp(c) {
        heap = new T[capacity];
    }
    ~PriorityQueue() { delete[] heap; }

    void enqueue(const T& item) {
        if (size == capacity) throw overflow_error("Queue full!");
        heap[size++] = item;
        siftUp(size - 1);
    }

    T dequeue() {
        if (size == 0) throw underflow_error("Queue empty!");
        T top = heap[0];
        heap[0] = heap[--size];
        siftDown(0);
        return top;
    }

    bool isEmpty() const { return size == 0; }
};

struct Patient { string name; int severity; }; // severity: 1=critical, 5=minor

int main() {
    // Higher severity number = lower priority (1 is most critical)
    auto triageCmp = [](const Patient& a, const Patient& b) {
        return a.severity < b.severity;
    };

    PriorityQueue<Patient, decltype(triageCmp)> er(10, triageCmp);

    er.enqueue({"Alice",  3});
    er.enqueue({"Bob",    1});  // critical
    er.enqueue({"Carol",  5});
    er.enqueue({"David",  2});
    er.enqueue({"Eve",    1});  // also critical

    cout << "=== Hospital Triage Queue ===" << endl;
    cout << "Treating patients (most critical first):" << endl;
    while (!er.isEmpty()) {
        Patient p = er.dequeue();
        cout << "  Treating: " << p.name << "  [Severity: " << p.severity << "]" << endl;
    }

    return 0;
}
