#include<vector>
#include<iostream>
using namespace std;

inline bool check_validity(int pos)
{
	return (pos<=0||pos>64)? false :true; 
}

const vector<int> *pentagonal_series(int pos)
{
	static vector<int> _elems;
	if(check_validity(pos) && (pos>_elems.size())) 
		for(int ix=_elems.size()+1;ix<=pos;++ix)
		    _elems.push_back(ix*(3*ix-1)/2);
	return &_elems;
}

bool pentagonal_elem(int pos,int &elem)
{
	if(!check_validity(pos))
	{
		cout<<"Sorry.Invalid position: "<<pos<<endl;
		elem=0;
		return false;
	}
	const vector<int> *pent=pentagonal_series(pos);
	elem=(*pent)[pos-1];
	return true;
}

int main()
{
	int elem,pos;
	
	while(cout<<"Please enter the pos:",cin>>pos)
	{
		if(pentagonal_elem(pos,elem))
		   cout<<"element "<<pos <<" is " <<elem <<'\n'; 
	}
	
}
