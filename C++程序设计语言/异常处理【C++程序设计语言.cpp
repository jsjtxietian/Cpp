#include<iostream>
#include<limits>
using namespace std; 

struct Range_error
{
	int i;
	Range_error(int ii)
	{
		i=ii;
	}
} ;

char to_char (int i)
{
	if(i<numeric_limits<char>::min() ||i>numeric_limits<char>::max())
	   throw Range_error(i);
	return i;
}

void h(int i)
{
	try
	{
		char c=to_char(i);
		cout << "correct!\n";
	}
		catch(Range_error x)
		{
			cerr << "oops:to_char (" << x.i <<")\n";
		}
}

int main()
{
	h(1290);
	h(1);
	return 0; 
} 
