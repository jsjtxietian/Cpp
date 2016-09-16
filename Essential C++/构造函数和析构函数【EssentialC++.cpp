#include<iostream>
#include<string>

using namespace std;

class Triangular
{
	public:
	//	Triangular ();
	//	Triangular (int len);
	/*   Triangular (const Triangular &rhs)
	        :_length(rhs._length),_beg_pos(rhs._beg_pos),_next(rhs._beg_pos-1)
	    {
		}
	*/
	/*	Triangular (int len,int bp)
            :_name("Triangular")
        {
        	_length=len>0 ? len :1;
			_beg_pos=bp >0 ? bp :1;
			_next=_beg_pos-1;
		} 
	*/	
	//const member functions
		int length() const {return _length;}
		int beg_pos const {return _beg_pos;}
		int elem(int pos) const;
		//non-const member functions	
		bool next(int &val);
		void net_reset(){_next=_beg_pos-1;} 
	private:
		string _name;
		int _length;
		int _beg_pos;
		int _next;
		
		static vector<int> _elems;
};

class Matrix
{
	public :
		Matrix(const Matrix &rhs);
/*		Matrix(int row,int col)
		  :_row(row),_col(col)
		{
			//资源配置
			_pmat=new double[row*col]; 
		}
		
		~Matrix()
		{
			//deatructor释放资源
			delete [] _pmat; 
		}
*/ 
	
	private:
		int _row,_col;
		double *_pmat;
}; 

int main()
{	
	return 0;
}


Matrix::Matrix(const Matrix &rhs) 
   :_row(rhs._row),_col(rhs._col)
{
	int elem_cnt=_row*_col;
	_pmat=new double[elem_cnt];
	
	for(int ix=0;ix<elem_cnt;++ix)
	  _pmat[ix]=rhs._pmat[ix];
}
/*
Triangular::Triangular()
{
	//default
	_length=1;
	_beg_pos=1;
	_next=0;
}
*/

int Triangular::elem(int pos) const
{
	return _elems[pos-1]; 
 } 

