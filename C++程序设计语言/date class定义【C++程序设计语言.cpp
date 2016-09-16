#include<iostream>
#include<string>

class Date
{
	public:
		enum Month{jan=1,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec};
		
		class Bad_data{ };  //异常类
		
		Date(int dd=0,Month mm=Month(0),int yy=0);//0 取默认
		
	//检查data的函数
	 	int day() const;
		Month month() const;
		int year()const;
		
		mutable string string_rep() const;      //字符串表示 
		void clear_rep(char s[]) const ;//C风格字符串  
		
		static void set_default(int ,Month ,int);
	//修改Date函数
		Date& add_year(int n);
		Date& add_month(int n);
		Date& add_day(int n); 
	private:
		int d,m,y;
		static Date default_date;
};

Date Date::default_date(22,jan,1901);

inline bool operator==(Date a, Date b)
{
	return a.day()==b.day() && a.month()==b.month() && a.year()==b.year() ;
}  

inline int Date::day() const
{
	return d; 
} 

inline int Date::year() const
{
	return y;
}

inline Month Date::month() const
{
	return m;	
}

Date& Date::add_month(int n)
{
	if(n==0) return *this;
	
	if(n>0)
	{
		int delta_y=n/12;
		int mm=m+n%12;
		if(mm>12)
		{
			delta_y++;
			mm-=12;
		}
		
		y+=delya_y;
		m=Month(mm);
		return *this;
	}
	
	return *this;
}

Date::Date(int dd,Month mm,int yy)
{
	if(yy==0)  yy=default_date.year();
	if(mm==0)  mm=default_date.month();
	if(dd==0)  dd=default_date.day();
	
	int max;
	
	switch(mm)
	{
		case feb:
			max=28+leapyear(yy);
			break;
		case apr:case jun:case sep:case nov:
			max=30;
			break;
		case jan:case mar:case may:case jul:case aug:case oct:case dec:
			max=31;
			break;
		default:
			throw Bad_date();
	}
	
	if(dd<1 || max<dd)
	   throw Bad_date();
	y=yy;
	m=mm;
	d=dd;
	
}

void f(Date& d)
{
	Date lvb_day = Date(16,Date::dec,d.year());
	if(d.day()==29 && d.month() ==Date::feb)
	{
		//
	}
	if(midnight())
	  d.add_day(1);
	cout << "day after : " <<d+1 << '\n'; 
}

