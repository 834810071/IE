#include <iostream>
#include <vector>

using namespace std;

int Mypartition(vector<int>& v, int l, int r) {
    int pivot = v[l];
    while (l < r) {
        while (l < r && v[r] > pivot) {
            --r;
        }
        if (l < r) {
            int t = v[r];
            v[r] = v[l];
            v[l] = t;
        }

        while (l < r && v[l] < pivot) {
            ++l;
        }

        if (l < r) {
            int t = v[r];
            v[r] = v[l];
            v[l] = t;
        }
    }

    v[l] = pivot;
    return l;
}



void quick_sort(vector<int>& v, int l, int r) {
    if (l >= r) {
        return ;
    }

    int p = Mypartition(v, l, r);
    quick_sort(v, l, p-1);
    quick_sort(v, p+1, r);
}


int main() {
    vector<int> v;
    v.push_back(0);
    v.push_back(2);
    v.push_back(1);
    v.push_back(5);
    v.push_back(4);
    v.push_back(9);
    v.push_back(7);
    v.push_back(8);
    quick_sort(v, 0, v.size()-1);
    for (auto& a : v) {
        cout << a << " ";
    }
    cout << endl;
    return 0;
}