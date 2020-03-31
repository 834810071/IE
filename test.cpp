#include <iostream>
#include <typeinfo>
using namespace std;

class A
{
public:
   virtual void Print() { cout<<"This is class A."<<endl; }
};

class B : public A
{
public:
    virtual void Print() { cout<<"This is class B."<<endl; }
};

int main()
{
    A *pA = new B();
    cout<<typeid(pA).name()<<endl; // class A *
    cout<<typeid(*pA).name()<<endl; // class A
    return 0;
}