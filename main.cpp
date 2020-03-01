#include <iostream>

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
    A a;
    A b = a;
    A c(a);
    b = c;
    return 0;
}