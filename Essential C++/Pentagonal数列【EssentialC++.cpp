#include<vector>
#include<string>
#include<iostream>
using namespace std;

extern void really_calc_elems(vector<int> &,int);
void display_elems(vector<int> &vec,const string &title,ostream &os=cout);

inline bool calc_elems(vector<int> &vec,int pos)
{
	if(pos<=0||pos>64)
	{
		cerr<<"Sorry.Invalid position:"
		    <<pos  <<endl;
		return false;
	}
	
	if(vec.size()<pos)
	   really_calc_elems(vec,pos);
	return true;	
}

int main()
{
	vector<int> pent;
	const string title("Pentagonal Numeric Series");
	
	int pos;
	
	while(cout<<"Please input position:",cin>>pos)
		if(calc_elems(pent,pos))
	  		 display_elems(pent,title);
	  		 
	return 0;
}

void really_calc_elems(vector<int> &vec,int pos)
{
	for(int ix=vec.size()+1;ix<=pos;++ix)
	   vec.push_back(ix*(3*ix-1)/2);
}

void display_elems(vector<int> &vec,const string &title,ostream &os)
{
	os<<'\n'<<title<<"\n\t";
	for(int ix=0;ix<vec.size();++ix)
	   os<<vec[ix]<<' ';
	os<<endl;
}
