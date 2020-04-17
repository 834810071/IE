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

class B
{
public:
    B()
    {

    }
    B(int b)
    {
        b = b;
    }
private:
    int b;
};

class A
{
public:
    A(B x) : b(x)
    {
        cout << "普通构造函数" << endl;
    }

    A(A&& a)
    {
        cout << "移动构造函数" << endl;
        this->b = a.b;
    }
    A(const A& a)
    {
        cout << "拷贝构造函数" << endl;

        this->b = a.b;
    }
private:
    B b;
};
int main()
{
    A a(11);
    A b(A(12));
    A c(move(a));
    return 0;
}