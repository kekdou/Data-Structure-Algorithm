#include <iostream>
#include <vector>

using std::vector;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void Select_Sort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(arr[i], arr[min_idx]);
        }
    }
}

void Select_Sort_Twoway(vector<int> &arr) {
    int n = arr.size();
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int min_idx = left;
        int max_idx = right;
        for (int j = min_idx + 1; j < max_idx; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
            if (arr[j] > arr[max_idx]) {
                max_idx = j;
            }
        }
        if (min_idx != left) {
            swap(arr[left], arr[min_idx]);
        }
        if (max_idx != right) {
            swap(arr[right], arr[max_idx]);
        }
        left++;
        right--;
    }
}

