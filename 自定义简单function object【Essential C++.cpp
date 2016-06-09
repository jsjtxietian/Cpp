#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

class LessThan
{
	public:
		bool operator()(const string &s1,const string &s2)
		{
			return s1.size()<s2.size();
		} 
};

template <typename elemType>
void display_vector(const vector<elemType> &vec,
					ostream &os=cout,int len=8)
{
	typename vector<elemType>::const_iterator  //!!!
	       iter = vec.begin(),
	       end_it=vec.end();
	
	int elem_cnt=1;
	while(iter!=end_it)
	   os<<*iter++
	    <<(!(elem_cnt++ % len)? '\n':' ');
	os<<endl;
}
 
int main()
{
	ifstream ifile("S:\\in.txt");
	ofstream ofile("S:\\out.txt");
	if(!ifile || ! ofile)
	{
		cerr<<"Uable to open file--bailing out!\n";
		return -1;
	}
	
	vector<string> text;
	string word;
	
	while(ifile>>word)
	  text.push_back(word);
	
	sort(text.begin(),text.end(),LessThan());
	display_vector(text,ofile);
	
	return 0;
} 
