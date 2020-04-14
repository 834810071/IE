#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <stack>
#include <climits>

using namespace std;

template<typename T>
int max1(T a, T b)
{
    return a > b ? a : b;
}
int main()
{
    srand((unsigned)time(NULL));
    cout << max1(3, 7) << endl;
    cout << max1(3.0, 7.0) << endl;
    //cout << max1(3, 7.0) << endl;
    return 0;
}