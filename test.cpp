#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;


int main()
{
    int n, m, t, Q;
    cin >> n >> m;
    vector<int> vec(n, 0);
    for (int i = 0; i < n; ++i)
    {
        cin >> t;
        vec[i] = t;
    }
    sort(vec.begin(), vec.end());
    cin >> Q;
    for (int i = 0; i < Q; ++i)
    {
        cin >> t;
        long long res = 0;
        int count = 1;
        for (int i = t-1; i >= 0; --i)
        {
            int tmp = m;
            while(tmp-- && i >= 0)
            {
                res += vec[i] * count;
                --i;
            }
            if (tmp != 0)
            {
                break;
            }
            ++i;
            ++count;
        }
        cout << res << endl;
    }
    return 0;
}