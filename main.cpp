#include <iostream>
#include <cstring>

using namespace std;

class A {

public:
    A() {
        cout << "A create！" << endl;
    }

    ~A() {
        cout << "A delete" << endl;
    }

    A& operator=(const A& a){
        cout << "赋值" << endl;
        return *this;
    }

    A(const A& a){
        cout << "拷贝" << endl;
    }
};

int main() {
    char* a = "你";
    char* b = "1";
    cout << sizeof(*a) << endl;
    cout << sizeof(*b) << endl;

    cout << sizeof(a) << endl;
    cout << sizeof(b) << endl;

    cout << typeof(a) << endl;
    cout << strlen(b) << endl;

    return 0;
}