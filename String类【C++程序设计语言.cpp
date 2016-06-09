
class String
{
	public:
		class Cref;
		
		class Range{ };
		
		String();
		String(const char*);
		String(const String&);
		String& operator=(const char*);
		String& operator=(const String&);
		~String(); 
		
		void check(int i) const {if(i<0 || i>=rep->sz)  throw Range();}
		
		char read(int i)const {return rep->s[i];}
		void write(int i,char c) {rep=rep->get_own_copy();rep->s[i]=c;}
		
		Cref operator[](int i){check(i);return Cref(*this,i);}
		char operator[](int i) const {check(i);return rep->s[i];}
		
		int size() const {return rep->sz};
		
		//... 
		
	private: 
		struct Srep;
		Srep *rep;
};

class String::Cref
{
	friend class String;
	String& s;
	int i;
	Cref(String& ss,int ii):s(ss),i(ii){}
	public:
		operator char() const{return s.read(i);}//产生值 
		void operator=(char c){s.write(i,c);} //修改值 
}

struct String::Srep
{
	public:
		char *s;
		int sz;
		int n;
		
		Srep(int nsz,const char *p)
		{
			n=1;
			sz=nsz;
			s=new char[sz+1];
			strcpy(s,p);
		}
		
		~Srep(){ delete[] s}
		
		Srep* get_own_copy()
		{
			if(n==1)
			  return this;
			n--;
			return new Srep(sz,s);
		}
		
		void assign(int nsz,const char *p)
		{
			if(sz!=nsz)
			{
				delete[] s;
				sz=nsz;
				s=new char[sz+1];
			}
			strcpy(s,p);
		}
	private:
		Srep(const Srep&);
		Srep& operator=(const Srep&);	
} ;

String::String()  //空串默认值 
{
	rep=new Srep(0,"");
}

String::String(const String& x)//复制构造函数 
{
	x.rep->n++;
	rep=x.rep; //共享表示 
}

String::~String()
{
	if(--rep->n==0)
	  delete rep;
}

String& String::operator=(const String& x) //复制赋值 
{
	x.rep->n++; //防止st=st 
	if(--rep->n==0) delete rep;
	rep=x.rep;
	return *this;
}

String::String(const char *s)
{
	rep=new Srep(strlen(s),s);
}

String& String::operator=(const char* s)
{
	if(rep->n==1)  //再利用Srep 
	{
		rep->assign(strlen(s),s);
	}
	else   //使用新Srep 
	{
		rep->n--;
		rep=new Srep(strlen(s),s);
	}
	return *this;
}

