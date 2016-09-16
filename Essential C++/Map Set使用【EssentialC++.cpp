#include<iostream>
#include<map>
#include<string> 
#include<set> 
using namespace std;

int main()
{
	map<string,int> words;
	set<string> word_exclusion;
	string tword;
	/*
	int ia[10]={1,3,5,8,5,3,1,5,8,1};
	vector<int>vec(ia,ia+10);
	set<int> iset(vec.begin(),vec.end());
	
	iset.insert(ival) ;
	iset.insert(vec.begin(),vec.end());
	
	set<int>::ilterator it=iset.begin();
	for(;it!=iset.end();++it)
	  cout<<*it<<' ' ;
	cout<<endl;
	*/ 
	words["vermeer"]=1;
	while(cin>>tword)
	{
		if(word_exclusion.count(tword))
		   continue;
		words[tword]++;
	}
	
	map<string,int>::iterator it=words.begin(); 
	for(;it!=words.end();++it)
	   cout << "key: " << it->first <<'\n'
	        << "\tvalue: "<<it->second << endl;
	        
	int count=0;
/*	it=words.find("vermeer");
	if(it!=words.end())
	   count=it->second;
*/
    string search_word("vermeer");
    if(words.count(search_word))
       count=words[search_word];
	cout<<count;
	
	return 0;
}

