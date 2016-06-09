#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>

using namespace std;


class Triangular_iterator
{
	public:
		Triangular_iterator(int index):_index(index-1){ };
		
		bool operator==(const Triangular_iterator& ) const;
		bool operator!=(const Triangular_iterator& ) const;
		
		friend int operator*(const Triangular_iterator &rhs);
		
		Triangular_iterator& operator++();//prefix
		Triangular_iterator operator++(int );//postfix
		
	private:
		void check_integrity() const;
		int _index;
};


class Triangular
{
	public:
		friend class Triangular_iterator;
		friend int operator*(const Triangular_iterator &rhs);
		
		typedef Triangular_iterator iterator;
		Triangular_iterator begin() const
		{
			return Triangular_iterator(_beg_pos);
		}
		Triangular_iterator end() const
		{
			return Triangular_iterator(_beg_pos + _length);
		}
		
		int length() const {return _length;}
		int beg_pos() const {return _beg_pos;}
		int elem(int pos) const {return _elems[pos-1]; }
		
		bool next(int &val) const;
		void next_reset() const { _next = _beg_pos-1; }
		
		static bool is_elem(int value);
		static void gen_elements(int length);
		static void gen_elems_to_value(int value);
		static void display(int length , int beg_pos, ostream &os=cout);
		
		Triangular(int len,int bp)
		   :_length(len > 0 ? len : 1),
		   _beg_pos(bp > 0 ? bp : 1)
		{
			_next = _beg_pos-1;
			int elem_cnt = _beg_pos + _length - 1;
			
			if(_elems.size() < elem_cnt)
			   gen_elements(elem_cnt);
		}
		Triangular(const Triangular &rhs)
		   :_length(rhs._length),_beg_pos(rhs._beg_pos),_next(rhs._beg_pos-1)
		{ }
		
		Triangular& copy(const Triangular &rhs);
		
	private:
		int _length;//元素数目 
		int _beg_pos;//起始位置 
		mutable int _next;//下一个迭代目标 
		
		static vector<int> _elems;
		static const int _max_elems = 1024;
};

vector<int> Triangular::_elems; 


ostream& operator<<(ostream &os,const Triangular &rhs) 
{
	os << "(" << rhs.beg_pos() << ", "
	   << rhs.length()         << ")";
	
	rhs.display(rhs.length(),rhs.beg_pos(),os);
	return os;
}

istream& operator>>(istream &is,Triangular &rhs)
{
	char ch1,ch2;
	int bp,len;
	
	//假设输入（3，6） 6 10 15 21 28 36
	//ch1=='（' ，bp=3,ch2==',',len=6
	is >> ch1 >> bp
	   >> ch2 >> len;
	
	Triangular tmp(len,bp);
	rhs=tmp;
	return is; 
}

inline bool Triangular_iterator::
operator==(const Triangular_iterator& rhs) const
{
	return _index==rhs._index;
}

inline bool Triangular_iterator::
operator!=(const Triangular_iterator& rhs) const
{
	return !(*this==rhs);
}

inline Triangular_iterator& Triangular_iterator::
operator++() 
{
	++_index;
	check_integrity();
	return *this;
}

inline Triangular_iterator Triangular_iterator::
operator++( int ) 
{
	Triangular_iterator tmp=*this;
	++_index;
	check_integrity();
	return tmp;
}

inline int operator*(const Triangular_iterator &rhs) 
{
	rhs.check_integrity();
	return Triangular::_elems[rhs._index];
}

inline void Triangular_iterator::check_integrity() const
{
	if(_index >= Triangular::_max_elems)
	{
		cerr<<"Overflow!!!\n";
		return ;
	}
	   
	   
	if(_index >= Triangular::_elems.size())
	   Triangular::gen_elements(_index+1);
}

Triangular& Triangular::copy(const Triangular &rhs)
{
	if(this != &rhs)
	{
		_length = rhs._length;
		_beg_pos = rhs._beg_pos;
		_next = rhs._beg_pos-1;
	}
	return *this;
}

void Triangular::gen_elements(int length)
{
	if(length<0 || length>_max_elems)
	{
		cerr<<length<<" out of range";
		return ;
	}
	
	if(_elems.size() < length)
	{
		int ix= _elems.size() ? _elems.size()+1 : 1;
		for(;ix<=length;++ix)
		   _elems.push_back(ix*(ix+1)/2);
	}
}

void Triangular::gen_elems_to_value(int value) //不需要static 
{
	int ix = _elems.size();
	if(!ix)
	{
		_elems.push_back(1);
		ix=1;
	}
	
	while(_elems[ix-1] >value && ix<_max_elems)
	{
		//cout<<"elems to value:" << ix*(ix+1)/2 <<endl;
		++ix;
		_elems.push_back(ix*(ix+1)/2);
	}
	
	if(ix==_max_elems)
	  cerr<<"value too large";
}


bool Triangular::next(int &val) const
{
	if(_next < _beg_pos + _length - 1)
	{
		val = _elems[_next++];
		return true;
	}
	return false;
}

bool Triangular::is_elem(int value)
{
	if(! _elems.size() ||
	   _elems[_elems.size()-1]<value)
	   gen_elems_to_value(value);
	   
	vector<int>::iterator found_it,
	                      end_it=_elems.end();
	found_it = find(_elems.begin(),end_it,value);
	return found_it != end_it;
}

int sum(const Triangular &train)
{
	if(!train.length())
	  return 0;
	
	int val,sum=0;
	train.next_reset();
	while(train.next(val))
	   sum+=val;
	return sum;
}

void Triangular::
display( int length, int beg_pos, ostream &os )
{
	if ( length <= 0 || beg_pos <= 0 ){
		 cerr << "invalid parameters -- unable to fulfill request: "
			  << length << ", " << beg_pos << endl;
		 return;
	}

	int elems = beg_pos + length - 1;

	if ( _elems.size() < elems )
		 gen_elements( elems );

	for ( int ix = beg_pos-1; ix < elems; ++ix )
		  os << _elems[ ix ] << ' ';
}

int main()
{
	/*
	Triangular tri(4,8);
	cout << "sum of elements: "
	     <<sum(tri) <<endl;
	*/
	
	/* 
	char ch;
	bool more=true;
	
	while(more)
	{
		cout << "Enter vaule: ";
		int ival;
		cin>>ival;
		
		bool is_elem = Triangular::is_elem(ival);
		
		cout<< ival
		    <<( is_elem ? " is " : " isn\'t ")
		    <<"an element in the Triangular series.\n"
		    <<"Another value?(y/n)";
		    
		cin>>ch;
		if(ch=='n'||ch=='N')
		   more=false;
	}
	*/ 
	
	Triangular train(20,12);
	Triangular::iterator 
	          it = train.begin(),
	          end_it = train.end();
	cout<<"Triangular Series of "<<train.length()<<" elements\n" << endl;
		
	while(it!=end_it)
	{
		cout<<*it<<' ';
		++it;
	}
	
	return 0;
}
