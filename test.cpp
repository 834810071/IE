#include <iostream>
using namespace std;

class MemoryBlock
{
public:

    // 构造器（初始化资源）
    explicit MemoryBlock(size_t length)
            : _length(length)
            , _data(new int[length])
    {
        cout << "普通构造函数" << endl;
    }

    // 析构器（释放资源）
    ~MemoryBlock()
    {
        if (_data != nullptr)
        {
            delete[] _data;
        }
    }

    // 拷贝构造器（实现拷贝语义：拷贝that）
    MemoryBlock(const MemoryBlock& that)
    // 拷贝that对象所拥有的资源
            : _length(that._length)
            , _data(new int[that._length])
    {
        cout << "普通拷贝函数" << endl;
        std::copy(that._data, that._data + _length, _data);
    }

    // 拷贝赋值运算符（实现拷贝语义：释放this ＋ 拷贝that）
    MemoryBlock& operator=(const MemoryBlock& that)
    {
        cout << "普通赋值函数" << endl;
        if (this != &that)
        {
            // 释放自身的资源
            delete[] _data;

            // 拷贝that对象所拥有的资源
            _length = that._length;
            _data = new int[_length];
            std::copy(that._data, that._data + _length, _data);
        }
        return *this;
    }

    // 移动构造器（实现移动语义：移动that）
    MemoryBlock(MemoryBlock&& that)
    // 将自身的资源指针指向that对象所拥有的资源
            : _length(that._length)
            , _data(that._data)
    {
        cout << "移动构造函数" << endl;
        // 将that对象原本指向该资源的指针设为空值
        that._data = nullptr;
        that._length = 0;
    }

    // 移动赋值运算符（实现移动语义：释放this ＋ 移动that）
    MemoryBlock& operator=(MemoryBlock&& that)
    {
        cout << "移动赋值函数" << endl;
        if (this != &that)
        {
            // 释放自身的资源
            delete[] _data;

            // 将自身的资源指针指向that对象所拥有的资源
            _data = that._data;
            _length = that._length;

            // 将that对象原本指向该资源的指针设为空值
            that._data = nullptr;
            that._length = 0;
        }
        return *this;
    }
private:
    size_t _length; // 资源的长度
    int* _data; // 指向资源的指针，代表资源本身
};

MemoryBlock f() { return MemoryBlock(50); }

int main()
{
    MemoryBlock a = f();            // 调用移动构造器，移动语义
    MemoryBlock b = a;              // 调用拷贝构造器，拷贝语义
    MemoryBlock c = std::move(a);   // 调用移动构造器，移动语义
    MemoryBlock d(MemoryBlock(50));
    a = f();                        // 调用移动赋值运算符，移动语义
    b = a;                          // 调用拷贝赋值运算符，拷贝语义
    c = std::move(a);               // 调用移动赋值运算符，移动语义
}