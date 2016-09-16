#include<iostream>
#include<vector>
#include<functional> 
#include<algorithm>
#include<iterator>

using namespace std;

template <typename InputIterator,typename OutputIterator,
         typename ElemType      ,typename Comp>
OutputIterator filter(InputIterator first,InputIterator last,
        OutputIterator at,const ElemType &val,Comp pred) 
{
	while((first =
	       find_if(first,last,bind2nd(pred,val)))!=last)
	{
		cout << "found value :"<< *first << endl;
		
		*at++=*first++;
	}
	return at;
}

vector<int> sub_vec(const vector<int> &vec,int val)
{
	vector<int> local_vec(vec);
	sort(local_vec.begin(),local_vec.end());
	
	vector<int>::iterator iter=
	     find_if(local_vec.begin(),
		         local_vec.end(),
				 bind2nd(greater<int>(),val));
	local_vec.erase(iter-1,local_vec.end());
	return local_vec;
}

int main()
{
	const int elem_size=8;
	
	int ia[elem_size]={12,8,43,0,6,21,3,7};
	vector<int> ivec(ia,ia+elem_size);
	
	int ia2[elem_size];
	vector<int> ivec2;
	
	cout << "filtering integer array for values less than 8\n";
	filter(ia,ia+elem_size,ia2,elem_size,less<int>());
	
	cout << "filtering integer vector for values greater than 8\n";
	filter(ivec.begin(),ivec.end(),back_inserter(ivec2),elem_size,greater<int>());
	
	cout << "filtering integer array for values less than 8\n";
	vector<int> iter=sub_vec(ivec,elem_size);
	for(int ix=0;ix<iter.size();ix++)
	   cout << "found value :"<< iter[ix] << endl;
	
	return 0;
}

/*bool less_than(int v1,int v2)
{
	return v1<v2 ? true :false;
}

bool greater_than(int v1,int v2)
{
	return v1>v2 ? true :false;
}

int count_occurs(const vector<int> &vec,int val)
{
	vector<int>::const_iterator iter=vec.begin();
	int occurs_count=0;
	while((iter=find(iter,vec.end(),val))!=vec.end())
	{
		++occurs_count;
		++iter;
	}
	return occurs_count; 
}
*/
