#include <iostream>
#include <vector>

using std::vector;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void Bubble_Sort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void Bubble_Sort_Flag(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void Bubble_Sort_Lastswap(vector<int> &arr) {
    int n = arr.size();
    int cur_boundary = n - 1;
    int last_swap = 0;
    while (cur_boundary > 0) {
        for (int j = 0; j < cur_boundary; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                last_swap = j;
            }
        }
        if (last_swap == 0) {
            break;
        }
        cur_boundary = last_swap;
    }
}

