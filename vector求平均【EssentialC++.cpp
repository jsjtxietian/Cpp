#include<iostream>
#include<vector>
using namespace std;

int main()
{
	vector<int> ivec;
	int ival;
	while(cin>>ival)
	   ivec.push_back(ival);
	   
	int sum=0;
	for(int ix=0;ix<ivec.size();++ix)
	   sum+=ivec[ix];
	   
	int average=sum/ivec.size();
	
	cout<<"Sum of "<<ivec.size()
		<<" elements:"<<sum <<'\t' 
		<<" Average: "<<average << endl;
	return 0;
}
