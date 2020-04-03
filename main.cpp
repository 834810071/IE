#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <algorithm>

using namespace std;
void help(vector<int>& arr, int l, int r);

void print(vector<int>& arr)
{
    for (int& i : arr)
    {
        cout << i << " ";
    }
    cout << endl;
}
void sort(vector<int>& arr)
{
    help(arr, 0, arr.size()-1);
}

void swap(vector<int>& arr, int x, int y)
{
    arr[x] ^= arr[y];
    arr[y] ^= arr[x];
    arr[x] ^= arr[y];
}

int digui(vector<int>& arr, int l, int r)
{
    if (l >= r)
    {
        return l;
    }
    int cur = arr[l];
    int index = l;

    while (l < r)
    {
        while (r >= l && arr[r] > cur)
        {
            --r;
        }
        if (r >= l && r != index)
        {
            swap(arr, r, index);
            index = r;
        }
       // print(arr);
        while (l < r && arr[l] < cur)
        {
            ++l;
        }
        if (l < r && l != index)
        {
            swap(arr, l, index);
            index = l;
        }
       // print(arr);
    }

    return l;
}

void help(vector<int>& arr, int l, int r)
{
    if (l >= r || r < 0  || l >= arr.size())
    {
        return;
    }
    int pa = digui(arr, l, r);
    cout << pa << endl;
    print(arr);
    help(arr, l, pa-1);
    help(arr, pa+1, r);
}

void* operator new(size_t size)
{
    cout << "new" << endl;
    malloc(sizeof(int));
}

int main()
{
    int *a = new int();
    return 0;
}