#include <iostream>
#include <vector>

using std::vector;

void Insert_Sort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j;
        for (j = i; j > 0 && arr[j - 1] > key; j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = key;
    }
}

int Binary_Search(vector<int> &arr, int begin, int end, int val) {
    int left = begin;
    int right = end - 1;
    int result = end;
    while (left <= right) {
        int index = (left + right) / 2;
        if (arr[index] >= val) {
            right = index - 1;
            result = index;
        } else {
            left = index + 1;
        }
    }
    return result;
}

void Insert_Sort_Binary(vector<int> &arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int index = Binary_Search(arr, 0, i, key);
        if (index < i) {
            for (int j = i; j > index; j--) {
                arr[j] = arr[j - 1];
            }
            arr[index] = key;
        }
    }
}

void Shell_Sort(vector<int> &arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int key = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > key; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = key;
        }
    }
}

