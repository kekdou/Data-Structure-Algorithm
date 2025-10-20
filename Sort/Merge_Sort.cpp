#include <iostream>
#include <vector>

using std::vector;

void Merge(vector<int> &arr, int left, int mid, int right) {
    vector<int> L;
    vector<int> R;
    for (int i = left; i <= mid; i++) {
        L.push_back(arr[i]);
    }
    for (int j = mid; j < right; j++) {
        R.push_back(arr[j]);
    }
    int i = 0;
    int j = 0;
    int k = left;
    while (i < mid - left + 1 && j < right - mid) {
        if (L[i] < R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < mid - left + 1) {
        arr[k++] = L[i++];
    }
    while (j < right - mid) {
        arr[k++] = R[j++];
    }
}

void Merge_Sort(vector<int> &arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        Merge_Sort(arr, left, mid);
        Merge_Sort(arr, mid + 1, right);
        Merge(arr, left, mid, right);
    }
}

