#include<iostream>

using namespace std;

template <typename T> 
class TypeToID
{
public:
    static int const ID = 0;
};

template <> 
class TypeToID<float>
{
public:
    static int const ID = -1;
};

template <typename T>                   // 嗯，需要一个T
class TypeToID<T*>                      // 我要对所有的指针类型特化，所以这里就写T*
{
public:
    typedef T        SameAsT;
    static int const ID = 0x80000000;   // 用最高位表示它是一个指针
};

template <>                             // 嗯，int* 已经是个具体的不能再具体的类型了，所以模板不需要额外的类型参数了
class TypeToID<int*>                    // 嗯，对int*的特化。在这里呢，要把int*整体看作一个类型。
{
public:
    static int const ID = 0x12345678;   // 给一个缺心眼的ID
};

int main()
{
    cout << "ID of float: " << TypeToID<float>::ID << endl;
	cout << "ID of float: " << TypeToID< TypeToID<float*>::SameAsT >::ID << endl; 
	cout << "ID of int*: " << TypeToID<int*>::ID << endl;
}

