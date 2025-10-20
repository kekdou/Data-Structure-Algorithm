#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

using std::list;
using std::vector;

void Sort(list<float> &bucket) {
    vector<float> temp_arr;
    for (float val : bucket) {
        temp_arr.push_back(val);
    }
    int n = temp_arr.size();
    for (int i = 1; i < n; i++) {
        int key = temp_arr[i];
        int j;
        for (j = i; j > 0 && temp_arr[j - 1] > key; j--) {
            temp_arr[j] = temp_arr[j - 1];
        }
        temp_arr[j] = key;
    }
    bucket.assign(temp_arr.begin(), temp_arr.end());
}

void Bucket_Sort(vector<float> arr) {
    int n = arr.size();
    int max_val = *std::max_element(arr.begin(), arr.end());
    int min_val = *std::min_element(arr.begin(), arr.end());
    if (max_val == min_val) {
        return;
    }
    int num_bucket = 10;
    vector<list<float>> bucket(num_bucket);
    for (float val : arr) {
        int index = static_cast<int>(num_bucket * (val - min_val) /
                                     (max_val - min_val));
        if (index == num_bucket) {
            index--;
        }
        bucket[index].push_back(val);
    }
    for (int i = 0; i < num_bucket; i++) {
        Sort(bucket[i]);
    }
    int index = 0;
    for (int i = 0; i < num_bucket; i++) {
        for (float val : bucket[i]) {
            arr[index++] = val;
        }
    }
}

