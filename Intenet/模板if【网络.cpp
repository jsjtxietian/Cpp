#include<iostream>

// ͨ��Ϊ�գ�����ƥ�������������ܺõĵ����ֶΣ������� bool ������ν�ˣ�
template<bool c, typename Then, typename Else> class IF_ { };

template<typename Then, typename Else>
class IF_<true, Then, Else> { public: typedef Then reType; };

template<typename Then, typename Else>
class IF_<false,Then, Else> { public: typedef Else reType; };

int main()
{
	const int len = 4;
	typedef
		IF_<sizeof(short)==len, short,
		IF_<sizeof(int)==len, int,
		IF_<sizeof(long)==len, long,
		IF_<sizeof(long long)==len, long long,
		void>::reType>::reType>::reType>::reType
	int_my; // ����һ��ָ���ֽ���������
	std::cout <<  sizeof(int_my) << std::endl ;
} 
