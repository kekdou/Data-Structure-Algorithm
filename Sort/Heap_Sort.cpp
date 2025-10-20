#incldue < iostream>
#include <vector>

using std::vector;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void siftdown(vector<int> &arr, int n, int parent) {
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;
    int largest = parent;
    if (left < n && arr[largest] < arr[left]) {
        largest = left;
    }
    if (right < n && arr[largest] < arr[right]) {
        largest = right;
    }
    if (largest != parent) {
        swap(arr[largest], arr[parent]);
        siftdown(arr, n, largest);
    }
}

void Heap_Sort(vector<int> &arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        siftdown(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        siftdown(arr, i, 0);
    }
}

