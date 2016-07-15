#include<iostream>

template <int N>
class aTMP
{
public:
    static const long long
		ret = N * aTMP<N-1>::ret;
};

template <>
class aTMP<0>
{
public:
	static const long long
		ret = 1;
};

int main()
{
	std::cout << aTMP<20>::ret << '\n';
	return 0;
}
