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
		fprintf(stderr,"�����ڴ�ʧ��\n");
		exit(1);
	}
	
	printf("�������ļ���:\n");
	scanf("%s",src);
	FILE* file = fopen(src,"w+");
	
	printf("����һ������:\n");
	getchar();
	fgets(buffer,MAX,stdin);
	fprintf(file,"%s",buffer);
	
	printf("������Ҫ�����Ĺؼ���:\n");
	fscanf(stdin,"%s",search_for);
	
	n = BruteSearch(buffer,search_for);
	
	printf("�ؼ��ֳ���%d��\n",n);
	
	system("pause");
	return 0;
}
