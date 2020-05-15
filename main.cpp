#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <sstream>
#include <unordered_set>

using namespace std;


int main()
{
    string str;
    cin >> str;
    if (str.length() >= 100)
    {
        cout << " " << endl;
        return 0;
    }
    unordered_set<char> s;

    for (int i = 0; i < str.length(); ++i)
    {
        if (s.count(str[i]))
        {
            cout << str[i] << endl;
            return 0;
        }
        else
        {
            s.insert(str[i]);
        }
    }
    cout << " " << endl;
    return 0;
}