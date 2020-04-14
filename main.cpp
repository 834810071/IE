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
class Solution {
public:
    /**
     *
     * @param version1 string字符串
     * @param version2 string字符串
     * @return int整型
     */
    int compareVersion(string version1, string version2) {
        // write code here
        if (version1 == version2)
        {
            return 0;
        }

        int i = 0, j = 0;
        int len1 = version1.length(), len2 = version2.length();
        while (i < len1 && j < len2)
        {
            if (version1[i] > version2[j])
            {
                return 1;
            }
            else if (version1[i] < version2[j])
            {
                return -1;
            }
            else
            {
                ++i;
                ++j;
            }
        }
        if (i < len1)
        {
            return 1;
        }
        else
        {
            return 1;
        }
    }
};

int main()
{
    return 0;
}