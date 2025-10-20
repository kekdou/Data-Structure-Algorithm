#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

void Count_Sort(vector<int> &arr) {
    int n = arr.size();
    int max_val = *std::max_element(arr.begin(), arr.end());
    vector<int> count(max_val + 1, 0);
    for (int num : arr) {
        count[num]++;
    }
    for (int i = 0; i < count.size() - 1; i++) {
        count[i + 1] += count[i];
    }
    vector<int> output(n);
    for (int i = n - 1; i >= 0; i--) {
        int cur_val = arr[i];
        int index = count[cur_val] - 1;
        output[index] = cur_val;
        count[cur_val]--;
    }
    arr = output;
}

void Count_Sort_Min(vector<int> &arr) {
    int n = arr.size();
    int max_val = *std::max_element(arr.begin(), arr.end());
    int min_val = *std::min_element(arr.begin(), arr.end());
    int offset = min_val;
    vector<int> count(max_val - min_val + 1, 0);
    for (int num : arr) {
        count[num - offset]++;
    }
    for (int i = 0; i < count.size() - 1; i++) {
        count[i + 1] += count[i];
    }
    vector<int> output(n);
    for (int i = n - 1; i >= 0; i--) {
        int cur_val = arr[i];
        int pos = count[cur_val - offset] - 1;
        output[pos] = cur_val;
        count[cur_val - offset]--;
    }
    arr = output;
}

