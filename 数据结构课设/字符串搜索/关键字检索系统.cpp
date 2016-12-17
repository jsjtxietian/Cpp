#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 10001
#define NUM 30

int BruteSearch(const char *text,const char *string)
{
	int n = 0 ;
	int len=strlen(string);
	
	static char lookup[UCHAR_MAX+1];
	lookup[0]=1;
	lookup[(unsigned char)(*string)]=2;
	
	for(;;text++ && text != '\0')
	{
		switch (lookup[(unsigned char )(*text)])
		{
			case 0:
				break;
			case 1:
			    return n;
			case 2:
			    if(strncmp(string+1,text+1,len-1)==0 )
			       n++;  
			    break;
			default:
				break;
		}
	} 	
	
}

int main()
{
	char *search_for=(char *)malloc(NUM);
	char *buffer=(char *)calloc(1,MAX);
	char *src = (char *)malloc(NUM);
	int n ;
	
	if(buffer==NULL || search_for==NULL || src == NULL)
	{
		fprintf(stderr,"分配内存失败\n");
		exit(1);
	}
	
	printf("请输入文件名:\n");
	scanf("%s",src);
	FILE* file = fopen(src,"w+");
	
	printf("输入一段洋文:\n");
	getchar();
	fgets(buffer,MAX,stdin);
	fprintf(file,"%s",buffer);
	
	printf("请输入要搜索的关键字:\n");
	fscanf(stdin,"%s",search_for);
	
	n = BruteSearch(buffer,search_for);
	
	printf("关键字出现%d次\n",n);
	
	system("pause");
	return 0;
}
