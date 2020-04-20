#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <algorithm>
#include <stack>

using namespace std;


struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};

class Solution {
public:
    vector<string> Permutation(string str) {
        vector<string> res;
        dfs(str, res, 0);
        sort(res.begin(), res.end());
        return res;
    }

    void dfs(string& str, vector<string>& res, int start)
    {
        if (start >= str.length())
        {
            res.push_back(str);
        }
        for (int i = start; i < str.length(); ++i)
        {
            swap(str[begin], str[i]);
            dfs(str, res, start+1);
            swap(str[begin], str[i]);
        }
    }

    void swap(char& a, char& b)
    {
        char t = a;
        a = b;
        b = t;
    }
};
int main() {
    Solution s;
    s.Permutation("abc");
    return 0;

}
