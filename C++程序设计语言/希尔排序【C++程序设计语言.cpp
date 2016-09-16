#include<iostream> 
#include<string.h>

using namespace std;

typedef int (*CFT)(const void *,const void *);

struct User
{
	char *name;
	char *id;
	int dept;
};

User heads[]={
	"xuxiaoxiang","xxx",11111,
	"chuhaoyun"  ,"chy",22222,			
	"taocong"	 ,"tC" ,33333,	
	"xuxincheng" ,"xxc",44444,
	"xietian"    ,"xt" ,55555,
	"suckit"     ,"si" ,66666
};

int cmp1(const void *p,const void *q)
{
	return strcmp(static_cast<const User*>(p)->name,static_cast<const User*>(q)->name);
}

int cmp2(const void *p,const void *q)
{
	return static_cast<const User*>(p)->dept - static_cast<const User*>(q)->dept;
}

void ssort(void *base,size_t n,size_t sz,CFT cmp)
{
	//对向量base元素递增排序  n数量 sz大小
	for(int gap=n/2;0<gap;gap/=2)
	{
		for(int i=gap;i<n;i++)
		{
			for(int j=i-gap;0<=j;j-=gap)
			{
				char* b=static_cast<char*>(base);//必须强制
				char* pj=b+j*sz; //&base[i]
				char *pjg=b+(j+gap)*sz;//&base[j+gap]
				
				if(cmp(pjg,pj)<0)
				{
					for(int k=0;k<sz;k++)
					{
						char temp=pj[k];
						pj[k]=pjg[k];
						pjg[k]=temp;
					}
				} 
			}
		}	
	} 
}



void print_id(User* v,int n)
{
	for(int i=0;i<n;i++)
	   cout<<v[i].name<<'\t'<<v[i].id<<'\t'<<v[i].dept<<'\n';
}

int main()
{
	cout<<"heads in alphabetical order:\n";
	ssort(heads,6,sizeof(User),cmp1);
	print_id(heads,6);
	cout<<'\n';
	
	cout<<"heads in order of department number:\n";
	ssort(heads,6,sizeof(User),cmp2);
	print_id(heads,6);
	return 0;
}
