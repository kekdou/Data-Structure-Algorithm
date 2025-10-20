#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::string;
using std::vector;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void siftup(vector<int> &heap, int index) {
    while (index > 0) {
        int parent_index = (index - 1) / 2;
        if (heap[index] < heap[parent_index]) {
            swap(heap[index], heap[parent_index]);
            index = parent_index;
        } else {
            break;
        }
    }
}

void siftdown(vector<int> &heap, int index) {
    int size = heap.size();
    int smallest = index;
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    if (left < size - 1 && heap[smallest] > heap[left]) {
        smallest = left;
    }
    if (right < size - 1 && heap[smallest] > heap[right]) {
        smallest = right;
    }
    if (smallest != index) {
        swap(heap[index], heap[smallest]);
        siftdown(heap, smallest);
    }
}

void push(vector<int> &heap, int val) {
    heap.push_back(val);
    siftup(heap, heap.size() - 1);
}

void pop(vector<int> &heap) {
    if (heap.empty()) {
        return;
    }
    heap[0] = heap.back();
    heap.pop_back();
    siftdown(heap, 0);
}

const int top(vector<int> &heap) {
    if (!heap.empty()) {
        return heap[0];
    } else {
        cout << "error!" << endl;
        return -1;
    }
}

const bool empty(vector<int> &heap) { return heap.empty(); }

void to_heap(vector<int> &array) {
    vector<int> heap = array;
    for (int i = heap.size() / 2 - 1; i > 0; i--) {
        siftup(heap, i);
    }
}

void display(vector<int> &heap) {
    if (heap.empty()) {
        cout << "heap is empty!" << endl;
        return;
    }
    int level = 0;
    int size = heap.size();
    while ((1 << level) - 1 < size) {
        level++;
    }
    int cur_node = 1;
    int cur_index = 0;
    cout << "------------" << endl;
    for (int i = 0; i < level; i++) {
        int indent = (1 << (level - 1 - i)) * 3;
        cout << string(indent, ' ');
        for (int j = 0; j < cur_node && cur_index < (size - 1); j++) {
            cout << left << setw(6) << heap[cur_index++];
            cout << string(2 * indent - 6, ' ');
        }
        cout << endl;
        cur_node *= 2;
    }
    cout << "------------" << endl;
}

