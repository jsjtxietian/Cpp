#include <iostream>

template<typename T, int i=1>
class someComputing 
{
public:
    typedef volatile T* retType; // ���ͼ���
    enum { retValume = i + someComputing<T, i-1>::retValume }; // ��ֵ���㣬�ݹ�
    static void f() { std::cout << "someComputing: i=" << i << '\n'; }
};
template<typename T> // ģ���������ݹ���ֹ����
class someComputing<T, 0> 
{
public:
    enum { retValume = 0 };
};

template<typename T>
class codeComputing 
{
public:
    static void f() { T::f(); } // �������͵��ú������������
};

int main()
{
    someComputing<int>::retType a=0;
    std::cout << sizeof(a) << '\n'; // 64-bit ����ָ��
    // VS2013 Ĭ�����ݹ����500��GCC4.8 Ĭ�����ݹ����900��-ftemplate-depth=n��
    std::cout << someComputing<int, 500>::retValume << '\n'; // 1+2+...+500
    codeComputing<someComputing<int, 99>>::f();
    return 0;
}
