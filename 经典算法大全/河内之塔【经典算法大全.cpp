#include<iostream>

using namespace std;

void hanoi(int n , char A ,char B , char C)
{
	if( n==1 )
		cout << "Move sheet " << n
			 << " from " << A 
			 << " to "   << C
			 <<endl;
	else
	{
		hanoi(n-1,A,C,B);
		cout << "Move sheet " << n
			 << " from " << A 
			 << " to "   << C
			 <<endl;
		hanoi(n-1,B,A,C);
	} 
}

int main()
{
	int n ;
	cin >> n ;
	hanoi(n,'A','B','C');
	return 0; 
}
