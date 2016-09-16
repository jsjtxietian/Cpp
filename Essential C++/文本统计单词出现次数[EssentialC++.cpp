#include<string>
#include<vector>
#include<iostream>

using namespace std;

class Assoc
{
	public:
		Assoc(){ }
		const double& operator[](const string&);
		double& operator[](string &);
		void print_all() const; 
	private:
		struct Pair
		{
			string name;
			double val;
			Pair(string n="",double v=0):name(n),val(v){}
		};
		vector<Pair>vec;
		
		Assoc(const Assoc&);
		Assoc& operator=(const Assoc&);
}; 

double& Assoc::operator[](string& s)
{
	for(vector<Pair>::iterator p=vec.begin();p!=vec.end();++p)
	   if(s==p->name)
	      return p->val;
	vec.push_back(Pair(s,0));
	return vec.back().val;
}

void Assoc::print_all()const
{
	for(vector<Pair>::const_iterator p=vec.begin();p!=vec.end();p++)
	   cout<< p->name << ": " <<p->val << '\n';
}

int main()
{
	string buf;
	Assoc vec;
	while(cin>>buf)
	  vec[buf]++;
	vec.print_all();
	
	return 0;
}
