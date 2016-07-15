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

// ���� 1^e+2^e+...+n^e
template<int N, int E>
class sum_pow 
{
    template<int i, int e> class pow_e{ public: enum{ ret=i*pow_e<i,e-1>::ret }; };
    template<int i> class pow_e<i,0>{ public: enum{ ret=1 }; };
    // ���� i^e��Ƕ����ʹ���ܹ�����Ƕ��ģ��Ԫ������private ���ʿ�������ʵ��ϸ��
    template<int i> class pow{ public: enum{ ret=pow_e<i,E>::ret }; };
    
    template<typename stat>
    class cond { public: enum{ ret=(stat::ri<=N) }; };
    
    template<int i, int sum>
    class stat 
	{ 
	public:
		typedef stat<i+1, sum+pow<i>::ret> Next;
        enum{ ri=i, ret=sum }; 
	};
	
public:
    enum{ ret = WHILE_<cond, stat<1,0> >::reType::ret };
};

int main() 
{
    std::cout << sum_pow<10, 2>::ret << '\n';
    return 0;
}
