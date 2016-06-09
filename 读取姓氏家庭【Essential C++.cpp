#include<map>
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;

typedef vector<string> vstring;

void poplate_map(ifstream &nameFile,map<string,vstring> &families)//读取文件
{
	string textline;
	while(getline(nameFile,textline))
	{
		string fam_name;
		vector<string> child;
		string::size_type pos=0, prev_pos=0, text_size=textline.size();
		//找出分隔符分隔开的单词 
		while((pos=textline.find_first_of(' ',pos))!=string::npos)
		{
			//计算子串终点
			string::size_type end_pos=pos-prev_pos;
			//prev_pos未设置 则读到的为家庭姓氏  否则读孩子的名字 
			if(!prev_pos)
			   fam_name=textline.substr(prev_pos,end_pos);
			else
			   child.push_back(textline.substr(prev_pos,end_pos));
			prev_pos=++pos;
		}

	//最后一个孩子
	if(prev_pos<text_size)
	  child.push_back(textline.substr(prev_pos,pos-prev_pos));
	  
	if(!families.count(fam_name))
	   families[fam_name]=child;
	else
	   cerr<<"Oops! We already have a " 
	       <<fam_name << "family in our map!\n";
	}       
}

void display_map(const map<string,vstring> &families,ostream &os)
{
	map<string,vstring>::const_iterator
	           it = families.begin(),
	           end_it=families.end();
	while(it!=end_it)
	{
		os<<"The " << it->first << " family";
		if(it->second.empty())
		   os << " has no children.\n";
		else
		{
			os<<" has  " <<it->second.size() <<" children:  ";
			vector<string>::const_iterator 
			      iter = it->second.begin(),
			      end_iter = it->second.end();
			while(iter!=end_iter)
			{
				os<<*iter<<" ";
				iter++;
			}
			os<<endl;
		}
		++it;
	}
}

void query_map(const string &family,const map<string,vstring> &families)
{
	map<string,vstring>::const_iterator
           it = families.find(family);
           
    if(it==families.end())
    {
    	cout << "Sorry ,The "<<family
    		 <<" is not currnetly entered.\n";
    	return ;
	}
	
	cout<<"The "<<family;
	if(!it->second.size())
	    cout<<" has no children\n";
	else
	{
		cout << " has " << it->second.size() <<" children: ";
		vector<string>::const_iterator 
			iter = it->second.begin(),
			end_iter=it->second.end();
		while(iter!=end_iter)
		{
			cout<< *iter++ <<" ";
		}
		cout<<endl;
	}
    
} 

int main()
{
	map<string,vstring> families;
	ifstream nameFile("S:\\in2.txt");
	
	if(!nameFile)
	{
		cerr<<"Unable to find namefile.\n";
		return -1;
	}
	
	poplate_map(nameFile,families);
	
	string family_name;
	
	while(1)
	{
		cout<<"Please enter a family name or q to quit :\n";
		cin>>family_name;
		
		if(family_name=="q")
			break;
		query_map(family_name,families);
	}
	display_map(families,cout);
	return 0;
}
