#include<vector>
#include<iostream>

using namespace std;

int ModularExponentiation(int base, int exp_in_bin, int modular);
vector<short> baseBexpansion(int num, short b);

int main()
{
	vector<short> a = baseBexpansion(2413, 16);

	for(vector<short>::iterator it = a.begin(); it != a.end(); it++)
	{
		cout<< *it;
	}

	cout<<endl;
//测试数据，981^937 mod 2537的结果应该是704  
	int x = ModularExponentiation(981, 937,2537);
	cout <<x <<endl;
}

}  
/** 
 * 计算 base^exp mod modular这个同余幂的值。 
 * base：底数 
 * exp_in_bin：指数 
 * modular：模 
 * return： 同余幂 
 */  


int ModularExponentiation(int base, int exp, int modular)
{

	vector<short> n = baseBexpansion(exp, 2);
	int x = 1; 
	
	int power = base % modular;
	for(int i = n.size() - 1; i > -1 ; i --)
	{
		if( n[i] ) { 
			
			x = (x * power)% modular;
		}
	
		power = (power * power) % modular;
	}

	return x;
}


/** 
45. * 计算数字num的b进制展开形式的数组 
46. * num：将被展开的数字 
47. * b：数字展开的基 
48. * return:数字展开后的向量，按照从左往右的顺序存储，如13的二进制展开为1101，存储的顺序也是{1,1,0,1} 
49. */  

vector<short> baseBexpansion(int num, short b)
{
	int q = num, i = 0, temp = 0;
	vector<short> a;
	while(q != 0)
	{
		a.push_back(q % b);
		q /= b;
	}


	int size = a.size();
	for(; i < size/2; i ++)
	{
		temp = a[i];
		a[i] = a[size-1-i];
		a[size-1-i] = temp;
	}
	return a;
}
