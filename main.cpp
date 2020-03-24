#include <iostream>
using namespace std;
struct A  // sizeof (A) == 12
{
    char b;
    int a;
    char c;
};
struct B  // sizeof (B) == 8
{
    char b;
    char c;
    int a;
};

int main() {
    cout << sizeof(A) << endl;
    cout << sizeof(B) << endl;
    return 0;
}