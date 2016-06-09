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
//�������ݣ�981^937 mod 2537�Ľ��Ӧ����704  
	int x = ModularExponentiation(981, 937,2537);
	cout <<x <<endl;
}

}  
/** 
 * ���� base^exp mod modular���ͬ���ݵ�ֵ�� 
 * base������ 
 * exp_in_bin��ָ�� 
 * modular��ģ 
 * return�� ͬ���� 
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
45. * ��������num��b����չ����ʽ������ 
46. * num������չ�������� 
47. * b������չ���Ļ� 
48. * return:����չ��������������մ������ҵ�˳��洢����13�Ķ�����չ��Ϊ1101���洢��˳��Ҳ��{1,1,0,1} 
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
