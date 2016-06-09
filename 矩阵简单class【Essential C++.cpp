#include<iostream>
#include<vector>
#include<ostream>

using namespace std;

class Matrix
{
	friend Matrix operator+(const Matrix&,const Matrix&) ;
	friend Matrix operator*(const Matrix&,const Matrix&) ;
	
	public:
		Matrix(const float *a);
		Matrix(float a11=0,float a12=0,float a13=0,
		       float a21=0,float a22=0,float a23=0,
			   float a31=0,float a32=0,float a33=0);
			
	    int rows() const { return 3;}
	    int cols() const { return 3;}
	    
	    float& operator()(int row,int col) { return _Matrix[row][col];}
	    float operator()(int row,int col) const { return _Matrix[row][col];}
	    void operator+=(const Matrix &);
	    
	    ostream& print(ostream&) const;
	    
	private:
		float _Matrix[3][3]; 
			
};

void Matrix::operator+=(const Matrix &m)
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			_Matrix[i][j]+=m(i,j);
		}
	}
}

Matrix operator*(const Matrix& a,const Matrix& b)
{
	Matrix result;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int p=0,q=0; p<3 && q<3 ; p++,q++)
			{
				result(i,j) += a(i,p) * b(q,j); 
			}
		}
	}
	
	return result;
}

Matrix::Matrix(float a11,float a12,float a13,
       float a21,float a22,float a23,
	   float a31,float a32,float a33)
{
	 _Matrix[0][0]=a11;
	 _Matrix[0][1]=a12;
	 _Matrix[0][2]=a13;
     _Matrix[1][0]=a21;
	 _Matrix[1][1]=a22; 
	 _Matrix[1][2]=a23;
	 _Matrix[2][0]=a31;
     _Matrix[2][1]=a32;
	 _Matrix[2][2]=a33;
}

Matrix::Matrix(const float *a)
{
	int index=0;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			_Matrix[i][j]=a[index++];
		}
	}
}

Matrix operator+(const Matrix& a,const Matrix& b)
{
	Matrix result(a);
	result+=b;
	return result;
}

ostream& Matrix::print(ostream& os) const
{
	int t=1;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cout<<_Matrix[i][j]<<' '; 
			if(t%3==0)
			   cout<<'\n';
			t++;
		}
	}
	return os;
}

inline ostream& operator<<(ostream& os,const Matrix &m) 
{
 	return m.print(os);
}

int main()
{
	float a[9]={1,2,3,4,5,6,7,8,9};
	Matrix m(a); 
	Matrix n(2,3,4,5,6,7,8,9,10);
	
	cout<<m*n;
	return 0;
}


 
