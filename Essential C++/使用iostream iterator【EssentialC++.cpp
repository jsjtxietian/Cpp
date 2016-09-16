#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>
#include<fstream>

using namespace std;

int main()
{
	vector<string> text;
	
/*
	ifstream in_file("input_file.txt");
	ofstream out_file("output_file.txt");
	
	if(!in_file || !out_file)
	{
		cerr<<"!!unable to open\n";
		return -1;
	}
	istream_iterator<string> is(in_file);
	istream_iterator<string> eof;
	
*/	
	istream_iterator<string> is(cin);
	istream_iterator<string> eof;
	
	copy(is,eof,back_inserter(text));
	sort(text.begin(),text.end());
	
	ostream_iterator<string> os(cout," ");
	//ostream_iterator<string> os(out_file," ");
	
    copy(text.begin(),text.end(),os);
	
	return 0;
}
