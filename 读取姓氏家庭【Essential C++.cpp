#include<map>
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;

typedef vector<string> vstring;

void poplate_map(ifstream &nameFile,map<string,vstring> &families)//��ȡ�ļ�
{
	string textline;
	while(getline(nameFile,textline))
	{
		string fam_name;
		vector<string> child;
		string::size_type pos=0, prev_pos=0, text_size=textline.size();
		//�ҳ��ָ����ָ����ĵ��� 
		while((pos=textline.find_first_of(' ',pos))!=string::npos)
		{
			//�����Ӵ��յ�
			string::size_type end_pos=pos-prev_pos;
			//prev_posδ���� �������Ϊ��ͥ����  ��������ӵ����� 
			if(!prev_pos)
			   fam_name=textline.substr(prev_pos,end_pos);
			else
			   child.push_back(textline.substr(prev_pos,end_pos));
			prev_pos=++pos;
		}

	//���һ������
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
