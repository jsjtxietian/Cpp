//P67
//Josephus Problem
#include<iostream>
#include<cmath>
using namespace std;

int method0(int);          //q = 2 only
int method1(int);          //q =3 only
int method2(int , int);

int main()
{
	cout << "请输入总人数以及每隔q-1人杀一人的q:\n";
	int N , q;
	cin >> N >> q; 
	cout << "最后一人是:" << method2(N,q) << endl; 
}


int method0(int n)        // n = 2^m + l    ->    live:2l+1
{
	int x = log10(n) / log10(2) ; 
	int l = n - pow(2,x);
	return 2*l+1;
}

int method1(int n)
{
	int N = 3*n;
	
	while(N > n)
		N = (N-n-1)/2 + N - n;
	
	return N;
}

int method2(int n , int q)
{
	int D = 1;
	
	while( D <= (q-1)*n )
	{
		D = (q*D+q-2) / (q-1);     //P79的底和顶转换公式 
		cout << D << endl;
	}
	return q*n+1-D;
}



