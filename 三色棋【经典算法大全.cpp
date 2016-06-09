#include<iostream>
#include<vector>

using namespace std;

int main()
{
	vector<char> c;
	char temp;
	while(cin >> temp)
		c.push_back(temp);
	int wFlag = 0 ;
	int bFlag = 0 ;
	int rFlag = c.size() - 1 ;
	
	while(wFlag <= rFlag)
	{
		if( c[wFlag] == 'w' )
			wFlag++;
		else if ( c[wFlag] == 'b' )
		{
			swap(c[bFlag] , c[wFlag]);
			bFlag++;
			wFlag++;
		}
		else
		{
			swap(c[wFlag] , c[rFlag]);
			rFlag--;
		}
	}
	 
	for(int i = 0 ; i < c.size() ; i++)
		cout << c[i] << ' '; 
	
	return 0;
}
