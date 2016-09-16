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

template <typename T>                   // �ţ���Ҫһ��T
class TypeToID<T*>                      // ��Ҫ�����е�ָ�������ػ������������дT*
{
public:
    typedef T        SameAsT;
    static int const ID = 0x80000000;   // �����λ��ʾ����һ��ָ��
};

template <>                             // �ţ�int* �Ѿ��Ǹ�����Ĳ����پ���������ˣ�����ģ�岻��Ҫ��������Ͳ�����
class TypeToID<int*>                    // �ţ���int*���ػ����������أ�Ҫ��int*���忴��һ�����͡�
{
public:
    static int const ID = 0x12345678;   // ��һ��ȱ���۵�ID
};

int main()
{
    cout << "ID of float: " << TypeToID<float>::ID << endl;
	cout << "ID of float: " << TypeToID< TypeToID<float*>::SameAsT >::ID << endl; 
	cout << "ID of int*: " << TypeToID<int*>::ID << endl;
}

