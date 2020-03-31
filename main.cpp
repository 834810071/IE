#include <iostream>
using namespace std;
//递归终止函数
void print()
{
    cout << "empty" << endl;
}



struct AA {

    int a;       //长度4 > 2 按2对齐；偏移量为0；存放位置区间[0,3]

    char b;  //长度1 < 2 按1对齐；偏移量为4；存放位置区间[4]

    short c;     //长度2 = 2 按2对齐；偏移量要提升到2的倍数6；存放位置区间[6,7]

    char d;  //长度1 < 2 按1对齐；偏移量为7；存放位置区间[8]；共九个字节

};

int main(void)
{
    cout << sizeof(AA) << endl;
    return 0;
}

1 2 3 4 5
4 1 5 9 2
1 0 1 1 0
  1     1