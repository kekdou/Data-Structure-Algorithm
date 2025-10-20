#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int Get_Digit(int val, int exp) { return (val / exp) % 10; }

void Sort(vector<int> &arr, int exp) {
    int n = arr.size();
    vector<int> count(10, 0);
    vector<int> output;
    for (int i = 0; i < n; i++) {
        int digit = Get_Digit(arr[i], exp);
        count[digit]++;
    }
    for (int i = 0; i < 9; i++) {
        count[i + 1] += count[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        int val = arr[i];
        int digit = Get_Digit(val, exp);
        int pos = count[digit] - 1;
        output[pos] = val;
        count[digit]--;
    }
    arr = output;
}

void Digit_Sort(vector<int> &arr) {
    int max_val = *std::max_element(arr.begin(), arr.end());
    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        Sort(arr, exp);
    }
}

