#include<iostream>
#include<vector>
#include<fstream>

using  namespace std;

void swap(int &val1,int &val2);
void bubble_sort(vector<int> &vec,ofstream *ofil=0);
template <typename elemType>
void display(vector<elemType> &vec,ostream &os=cout);


int main()
{
	int ia[8] = {8,34,3,13,1,21,5,2};
	vector<int> vec (ia,ia+8);
	
	//ofstream ofil("text.txt");
	bubble_sort(vec);//bubble_sort (vec,ofil);
	
	display(vec);//display(vec,ofil);
	
	return 0;
} 

void swap(int &val1,int &val2)
 {
 	int temp=val1;
 	val1=val2;
 	val2=temp;
 }
 
template <typename elemType>
void display(vector<elemType> &vec,ostream &os)
{
	for(int ix=0;ix < vec.size() ;++ix)
	{
		os << vec[ix] << ' ';
	}
	os << endl;
 } 
 
 void bubble_sort(vector<int> &vec,ofstream *ofil)
 {
 	for (int ix=0;ix<vec.size();++ix)
 	{
 		for (int jx=ix+1; jx<vec.size();++jx)
 		{
 			if(vec[ix]>vec[jx])
 			{
 				if(ofil != 0)
 				{
 					(*ofil) << "about to call swap! " << ix << " " << jx <<endl;
				}
 				swap(vec[ix],vec[jx]);
			}
		}
	}
}
 
