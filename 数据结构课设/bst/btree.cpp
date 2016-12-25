// BSTree.cpp : �������̨Ӧ�ó������ڵ㡣

#include <iostream>
#include "btree.h"

using namespace std;

int main()
{
	BSTree<int> s ;
	
	cout<< "**     ����������          **" << '\n'
		<< "=============================" << '\n'
		<< "**     1---��������������  **" << '\n'
		<< "**     2---����Ԫ��        **" << '\n'
		<< "**     3---��ѯԪ��        **" << '\n'
		<< "**     4---�˳�����        **" << endl;
	
	int order;

	while(cout << "\nplease input order : " , cin >> order)
	{
		switch( order)
		{
			case 1:
				create(s);
				break;
				
			case 2:
				insert(s);
				break;
				
			case 3:
				search(s);
				break;
				
			case 4:
				s.destory();
				return 0;
				
			default :
				cout << "ָ����� ���������룺" << endl;
				break; 
								
		}
	}	
	
	return 0;	 
}

void search(BSTree<int>& s)
{
	int a;
	cout<<"������Ҫ���ҵ�����"<<endl;
	cin >> a;
	
	BSTNode<int>* findnode = s.search(a);
	if(!findnode)
	{
		cout<<"����ʧ��"<<endl;
	}
	else
	{
		cout<<findnode->_key<<"���ҳɹ�"<<endl;
	}
}

void create(BSTree<int> &s)
{
	cout<<"���������������Թ�������������"<<endl;
	getchar();
	
	while(cin.get() != '\n')
	{
		cin.unget();
		int a ;
		cin >> a;
		
		BSTNode<int>* findnode = s.search(a);
		if(findnode)
		{
			cout << a << "��ֵ�Ѵ��ڣ�" << endl;
			continue; 
		}
		else
			s.insert(a);
	}
	cout << "�������:" ;	
	s.inOrder();	
	cout << endl;		
}

void insert(BSTree<int> &s)
{
	int a ;
	cout << "������Ҫ�����ֵ��" << endl;
	cin >> a ;
		
	BSTNode<int>* findnode = s.search(a);
	if(findnode)
	{
		cout << "��ֵ�Ѵ��ڣ�" << endl;
	}
	else
	{
		s.insert(a); 
		cout << "�������:" ;	
		s.inOrder();	
	}

}
