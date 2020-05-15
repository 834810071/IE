#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <sstream>

using namespace std;

class A
{
public:
    A(int l) :  l(l)
    {

    }
    A(int v, int l) : val(v), l(l)
    {

    }
    int val;
    int l;

};

bool cmp(A a, A b)
{
    if (a.val == b.val)
    {
        return a.l < b.l;
    }
    return a.val > b.val;
}

int main()
{
    int len;
    cin >> len;
    vector<A> arr;
    string lens, vs;
    cin >> lens;
    cin >> vs;
    int s = 0;
    for (int i = 0; i < lens.size(); ++i)
    {
        if (lens[i] == ',')
        {
            arr.push_back(A(atoi(lens.substr(s, i).c_str())));
            s = i+1;
        }
    }
    arr.push_back(A(atoi(lens.substr(s).c_str())));
    s = 0;
    int t = 0;
    for (int i = 0; i < vs.size(); ++i)
    {
        if (vs[i] == ',')
        {
            arr[t++].val = atoi(vs.substr(s).c_str());
            s = i+1;
        }
    }
    arr[t++].val = atoi(vs.substr(s).c_str());

    int res = 0;
    sort(arr.begin(), arr.end(), cmp);
    int cur = len;
    for (int i = 0; i < arr.size(); ++i)
    {
        if (arr[i].l <= cur)
        {
            cur -= arr[i].l;
            res += arr[i].val;
        }
        else
        {
            break;
        }
    }
    cout << res << endl;
    return 0;
}