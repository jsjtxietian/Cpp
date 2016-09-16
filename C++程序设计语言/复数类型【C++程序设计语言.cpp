
class complex
{
	public:
		complex& operator+=(complex a);
		complex& operator+=(double a);
		complex(double r=0,double i=0):re(r),im(i){ } 
		double real() const {return re;}
		double imag() const {return im;} 
		//...
	private:
		double re,im; 
};
//¸¨Öúº¯Êý 
complex(const complex& c):re(c.re),im(c.im){ }//must &
bool operator==(complex a ,complex b); 
	
complex operator+(complex a,complex b)
{
	cpmplex r=a;
	return r+=b;
}

complex operator+(complex a,double b)
{
	cpmplex r=a;
	return r+=b;
}

complex operator+(double a,complex b)
{
	cpmplex r=b;
	return r+=a;
}

inline complex& complex::operator+=(complex a)
{
	re+=a.re;
	im+=a.im;
	return *this;
}

inline complex& complex::operator+=(double a)
{
	re+=a;
	return *this;
}

inline bool operator==(complex a ,complex b)
{
	return a.real()==b.real() && a.imag()==b.imag();
}
