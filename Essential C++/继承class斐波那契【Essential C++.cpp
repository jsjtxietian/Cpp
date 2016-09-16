#include<vector>
#include<iostream>
#include<typeinfo>
#include<algorithm> 

using namespace std; 

class num_sequence;
ostream& operator<<( ostream &os, const num_sequence &ns );

class num_sequence
{
	public:
		typedef vector<unsigned int>::iterator iterator;
		  
		virtual               ~num_sequence(){ };
		virtual num_sequence *clone() const =0;
		
		unsigned int          elem(int pos) const;
		bool                  is_elem(unsigned int) const;
		int                   pos_elem(unsigned int) const;
		
		const char*           what_am_i() const;
		static int            max_elems() { return _max_elems; }
		ostream&              print( ostream &os=cout ) const;
		
		int                   length()  const { return _length;}
		int                   beg_pos() const  { return _beg_pos;}
		
		iterator begin() const 
			{ return _relems.begin() + _beg_pos-1;}
		iterator end() const
			{ return _relems.begin()+ _beg_pos + _length;}
		
		void set_position(int pos);
		void set_length(int pos);
		
		bool operator==(const num_sequence &) const;
		bool operator!=(const num_sequence &) const;
		
		const vector<unsigned int>* sequence() const
			{ return &_relems; }
		
	protected:
		enum { _max_elems = 1024};
		
		virtual void gen_elems(int pos ) const = 0 ;
		bool         check_integrity(int pos ,int size) const ;
		int          _calc_pos( unsigned int ) const;
		
		num_sequence( int beg_pos, int len, 
			  vector< unsigned int> &re ) : _relems( re )
		{ 
			set_position( beg_pos ); 
			set_length( len ); 
		}
		
		int           _beg_pos;
		int           _length;	
		vector<unsigned int>  &_relems;
}; 

ostream& operator<<(ostream &os,const num_sequence &ns)
{
	return ns.print(os);
}

inline bool num_sequence::
operator==(const num_sequence & rhs) const
{
	return ( _beg_pos == rhs._beg_pos ) &&
		   ( _length  == rhs._length );
}

inline bool num_sequence::
operator!=(const num_sequence & rhs) const
{
	return !(*this==rhs);
}

inline void num_sequence::
set_position(int pos)
{
	if(pos<=0 || pos> _max_elems)
	{
		cerr<<"!invalid position"
		    <<"set it to default 1";
		pos=1;
	}
	_beg_pos = pos;
}

inline void num_sequence::
set_length(int len)
{
	if(len <=0 || len + _beg_pos > _max_elems)
	{
		cerr<<"!invalid length"
		    <<"set it to default 1";
		len = 1;
	}
	_length = len;
}


inline unsigned int num_sequence::
elem(int pos )const
{
	return (! check_integrity(pos,_relems.size())) ? 0 : _relems[pos-1];
}

inline const char *
num_sequence::what_am_i() const
{
	return typeid(*this).name();	
}

inline bool num_sequence::
check_integrity(int pos,int size) const
{
	bool status = true;
	
	if(pos <= 0 || pos>64)
	{
		cerr<<"invalid position :"<<pos<<endl;
		status = false;
	}
	else if(pos>size)
	{
		gen_elems(pos);
	}
	return status; 
} 

inline bool num_sequence::
is_elem(unsigned int elem) const
{
	return (!check_integrity(_beg_pos,_length)) ? false : binary_search(begin(),end(),elem);
}

ostream& num_sequence::print( ostream &os) const
{
	int elem_pos = _beg_pos-1;
	int end_pos  = elem_pos + _length;
	
	if(!check_integrity(end_pos,_relems.size()))
	{
		return os;
	}
	
	os<<"("
	  <<_beg_pos << " , "
	  <<_length<<" ) ";
	  
	while(elem_pos < end_pos )
	{
		os << _relems[ elem_pos++] <<' ';
	}
	return os; 
}

int num_sequence::
pos_elem(unsigned int elem ) const
{
	cout << "pos_elem( " << elem << " )\n";

	if ( _relems[ _relems.size()-1 ] < elem )
		 return _calc_pos( elem );

	iterator iter = find( _relems.begin(), _relems.end(), elem );
	return ( iter == _relems.end() )
		     ? 0 
			 : distance( _relems.begin(), iter )+1;
}

int num_sequence::
_calc_pos( unsigned int elem ) const
{
	int pos = _relems.size()-1;

    cout << "calc_pos invoked()!: elem: " << elem 
		 << " pos: " << pos 
		 << " at: "  << _relems[ pos ] 
		 << "\n";

	while (( pos < _max_elems ) && 
		   ( _relems[ pos ] < elem ))
	{
		   gen_elems( ++pos ); 
		   cout << " pos: " << pos 
		        << " at: "  << _relems[ pos ] << endl;
	}

	return (( pos < _max_elems ) && 
		   ( _relems[pos] == elem )) ? pos+1 : 0;
}


class Fibonacci : public num_sequence {
public:
   Fibonacci( int beg_pos = 1, int len = 1 )
           :  num_sequence( beg_pos, len, _elems ){}

   virtual num_sequence *clone() const 
		 { return new Fibonacci( *this ); }
		
protected:
   virtual void gen_elems( int pos ) const;
   static vector< unsigned int> _elems;
};


vector<unsigned int> Fibonacci::_elems;

void Fibonacci::
gen_elems( int pos ) const
{   
	if ( pos <= 0 || pos > max_elems() )
		 return;

    if ( _elems.empty() )
       { _elems.push_back( 1 ); _elems.push_back( 1 ); }

    if ( _elems.size() <= pos )
	{
		    int ix = _elems.size();
			int n_2 = _elems[ ix-2 ], 
				n_1 = _elems[ ix-1 ];

			int elem;
			for ( ; ix <= pos; ++ix ){
				    elem = n_2 + n_1; 
					_elems.push_back( elem );
					n_2 = n_1; n_1 = elem;
			}
	 }
}


int main()
{
	Fibonacci f(8,12);
	cout<<f;
		
	return 0;
}
