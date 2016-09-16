//给定正整数mn，计算最大公因子d和整数a，b使得am+bn = d 
#include<iostream>
using namespace std;

int main()
{
    int m , n;
    cin >> m >> n;
    
    int a2 = 1, b1 = 1 ;
    int a1 = 0 ,b2 = 0;
    int c = m , d = n;
    
    int q , r , t;
	
	q = c / d ;
	r = c % d ;
	
	while( r != 0)
	{
		c = d ;
		d = r ;
		t = a2 ;
		a2 = a1 ;
		a1 = t - q * a1;
		t = b2;
		b2 = b1;
		b1 = t - q * b1;
		
		q = c / d ;
		r = c % d ;
	}
	
	cout << a1 << "*" << m 
		 << b1 << "*" << n
		 << "=" << d << endl;
	 
    return 0;
}
