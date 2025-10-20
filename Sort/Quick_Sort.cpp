#include <iostream>
#include <random>
#include <vector>

using std::vector;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int Partition(vector<int> &arr, int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[j], arr[i]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

void Quick_Sort(vector<int> &arr, int left, int right) {
    if (left < right) {
        int pos = Partition(arr, left, right);
        Quick_Sort(arr, left, pos - 1);
        Quick_Sort(arr, pos + 1, right);
    }
}

int Partition_Random(vector<int> &arr, int left, int right) {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> int_dist(left, right);
    int index = int_dist(eng);
    int pivot = arr[index];
    swap(arr[right], arr[index]);
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[j], arr[i]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

int Partition_Mid(vector<int> &arr, int left, int right) {
    int mid = (left + right) / 2;
    int index = arr[mid] > arr[left] ? mid : left;
    index = arr[mid] < arr[right] ? mid : right;
    int pivot = arr[index];
    swap(arr[right], arr[index]);
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[j], arr[i]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

void Partition_ThreeWay(vector<int> &arr, int left, int right, int &lt,
                        int &gt) {
    int pivot = arr[left];
    lt = left;
    gt = right;
    int i = left + 1;
    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(arr[i++], arr[lt++]);
        } else if (arr[i] > pivot) {
            swap(arr[i], arr[gt--]);
        } else {
            i++;
        }
    }
}

void Quick_Sort_ThreeWay(vector<int> &arr, int left, int right) {
    if (left < right) {
        int lt, gt;
        Partition_ThreeWay(arr, left, right, lt, gt);
        Quick_Sort_ThreeWay(arr, left, lt - 1);
        Quick_Sort_ThreeWay(arr, gt + 1, right);
    }
}

