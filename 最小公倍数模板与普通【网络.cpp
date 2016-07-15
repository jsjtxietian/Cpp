#include<iostream> 

// ͨ��Ϊ�գ�����ƥ�������������ܺõĵ����ֶΣ������� bool ������ν�ˣ�
template<bool c, typename Then, typename Else> class IF_ { };
template<typename Then, typename Else>
class IF_<true, Then, Else> { public: typedef Then reType; };
template<typename Then, typename Else>
class IF_<false,Then, Else> { public: typedef Else reType; };

// ����Ҫ�� Condition ����ֵ ret��Statement ������ Next
template< template<typename> class Condition, typename Statement>
class WHILE_ 
{
    template<typename statement> class STOP { public: typedef statement reType; };
public:
    typedef typename
        IF_<Condition<Statement>::ret,
        WHILE_<Condition, typename Statement::Next>,
        STOP<Statement>>::reType::reType
    reType;
};
// ��С����������ͨ����
int lcm(int a, int b)
{
    int r, lcm=a*b;
    while(r=a%b) 
	{ 
		a = b;
		b = r; 
	} // ��Ϊ�ÿɱ�Ĵ洢������д�� a=b; b=a%b;
    return lcm/b;
}
// �ݹ麯���汾
int gcd_r(int a, int b) { return b==0 ? a : gcd_r(b, a%b); } // ���
int lcm_r(int a, int b) { return a * b / gcd_r(a,b); }

//ģ��汾
template<int A, int B>
class lcm_T{
    template<typename stat>
    class cond { public: enum{ ret=(stat::div!=0) }; };
    
    template<int a, int b>
    class stat { public: typedef stat<b, a%b> Next; enum{ div=a%b, ret=b }; };
    
    static const int gcd = WHILE_<cond, stat<A,B>>::reType::ret;
    
public:
    static const int ret = A * B / gcd;
};

// �ݹ�ģ��汾
template<int A, int B>
class lcm_T_r
{
    template<int a, int b> class gcd { public: enum{ ret = gcd<b,a%b>::ret }; };
    template<int a> class gcd<a, 0> { public: enum{ ret = a }; };
public:
    static const int ret = A * B / gcd<A,B>::ret;
};

int main() {
    std::cout << lcm(100, 36) << '\n';
    std::cout << lcm_r(100, 36) << '\n';
    std::cout << lcm_T<100, 36>::ret << '\n';
    std::cout << lcm_T_r<100, 36>::ret << '\n';
    return 0;
}
