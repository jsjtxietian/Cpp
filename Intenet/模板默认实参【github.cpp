#include <type_traits>
#include <iostream>
#include <complex>
using namespace std; 

template <typename T> 
T CustomDiv(T lhs, T rhs) 
{
    T v;
    // Custom Div的实现
    return v;
}

template < typename T,
    	   typename Enabled = std::true_type
    	 > 
struct SafeDivide 
{
    static T Do(T lhs, T rhs) 
	{
        return CustomDiv(lhs, rhs);
    }
};

template <typename T> 
struct SafeDivide<T, typename std::is_floating_point<T>::type>
{    // 偏特化A
    static T Do(T lhs, T rhs)
	{
        return lhs/rhs;
    }
};

template <typename T> 
struct SafeDivide<T, typename std::is_integral<T>::type>
{   // 偏特化B
    static T Do(T lhs, T rhs)
	{
        return rhs == 0 ? 0 : lhs/rhs;
    }
};

int main()
{
	cout << SafeDivide<float>::Do(1.0f, 2.0f) << '\n'            // 调用偏特化A
         << SafeDivide<int>::Do(4, 2)  << '\n'					// 调用偏特化B
		 << SafeDivide<std::complex<float>>::Do({1.f, 2.f}, {1.f, -2.f})// 调用一般形式
		 << endl; 
    
}
