#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>

using namespace std;

//bool fibon_elem(int pos,int &); 
bool print_sequence(int pos); 
inline bool is_size_ok(int size);
const vector<int> *fibon_seq(int size);
inline bool seq_elem(int pos,int &elem,const vector<int>* (*seq_ptr)(int));

enum ns_type
{
	ns_fibon
};

int main()
{
	int pos;
	cout << "Please enter a pos:";
	cin >> pos;
	
	const vector<int>* (*seq_array[])(int)={fibon_seq};
	const vector<int>* (*seq_ptr)(int)=seq_array[ns_fibon];
	
	int elem;
	if(seq_elem(pos,elem,seq_ptr))
	{
		cout << "element # "<<pos
		     << " is " << elem <<endl;
		print_sequence(pos);
	}
	else
	{
		cout << "Sorry .could not caculate element #"
		     <<pos << endl;
	}
}

bool is_size_ok(int size)
{
	const int max_size=1024;
	static vector<int> elems;
	
	if(size<=0 || size>max_size)
	{
		cerr << "fibon_seq(): oops:invalid size :  "
		     <<size  << " --can't fulfill request.\n";
		return false;
	}
	return true;
}


const vector<int> *fibon_seq(int size)
{	
	const int max_size=1024;
	static vector<int> elems;
	
	if(! is_size_ok(size))
	{
		return 0;
	}
	
	for(int ix=elems.size();ix<size;++ix)
	{
		if(ix==0||ix==1)
		   elems.push_back(1);
		else
		   elems.push_back(elems[ix-1]+elems[ix-2]);
	}
	return &elems;
} 


bool seq_elem(int pos,int &elem,const vector<int>* (*seq_ptr)(int))
{
	if(!seq_ptr)
	{
		cout << "Internal Error:seq_ptr is set to null";
	}
	
	const vector<int> *pseq = seq_ptr(pos);
	
	if(!pseq)
	{
		elem=0;
		return false;
	}
	elem=(*pseq)[pos-1];
	return true;
}

/*
bool fibon_elem(int pos,int &elem)
{
	if(pos<=0||pos>1024)
	{
		elem=0;
		return false;
	}
	elem=1;
	int n_2=1,n_1=1;
	for(int ix=3;ix<=pos;++ix)
	{
		elem=n_2+n_1;
		n_2=n_1;
		n_1=elem;
	}
	
	return elem;
}
*/
bool print_sequence(int pos)
{
	if(pos<=0 || pos>1024)
	{
		cerr <<" invalid position:  "<<pos
		     <<" --can not handle request£¡\n";
		return false;
	}
	
	cout << "The Fibonacci Sequence for "
	     << pos << " psitions: \n\t";
	switch(pos)
	{
		default:
		case 2:
			cout << "1 ";
		case 1:
			cout << "1 ";
			break;
	}
	
	int elem;
	int n_2=1,n_1=1;
	for(int ix=3; ix<=pos; ++ix)
	{
		elem=n_2+n_1;
		n_2=n_1;
		n_1=elem;
		
		cout << elem << (!(ix%10)? "\n\t" :" ");
	}
	cout << endl;
	return true;
}

