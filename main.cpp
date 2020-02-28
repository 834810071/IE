#include <memory>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;


void test();

int selectPivot(vector<int>& arr, int s, int e) {
    int mid = (s + e) / 2;
    int a[3] = {arr[s], arr[mid], arr[e]};
    sort(a, a+3);
    return a[0];
};



int quick_sort(vector<int>& arr, int s, int e) {

    int pivot = selectPivot(arr, s, e);
    while (s < e) {
        while (s < e && arr[e] >= pivot)
            --e;
        if (s < e) {
            int tmp = arr[s];
            arr[s] = arr[e];
            arr[e] = tmp;
        }
        while (s < e && arr[s] <= pivot) {
            ++s;
        }

        if (s < e) {
            int tmp = arr[s];
            arr[s] = arr[e];
            arr[e] = tmp;
        }
    }
    arr[s] = pivot;
    return s;
}

void quick(vector<int>& arr, int s, int e) {
    if (s >= e) {
        return ;
    }
    int p = quick_sort(arr, s, e);
    quick(arr, s, p-1);
    quick(arr, p+1, e);
}

int main()
{
    vector<int> arr = {1,2,5,6,0,3,5,8,9,10,3,6};
    quick(arr, 0, arr.size()-1);
    for (auto& i : arr) {
        cout << i << " ";
    }
    return 0;
}