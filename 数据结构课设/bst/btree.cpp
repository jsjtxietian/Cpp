// BSTree.cpp : 定义控制台应用程序的入口点。

#include <iostream>
#include "btree.h"

using namespace std;

int main()
{
	BSTree<int> s ;
	
	cout<< "**     二叉排序树          **" << '\n'
		<< "=============================" << '\n'
		<< "**     1---建立二叉排序树  **" << '\n'
		<< "**     2---插入元素        **" << '\n'
		<< "**     3---查询元素        **" << '\n'
		<< "**     4---退出程序        **" << endl;
	
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
				cout << "指令错误 请重新输入：" << endl;
				break; 
								
		}
	}	
	
	return 0;	 
}

void search(BSTree<int>& s)
{
	int a;
	cout<<"请输入要查找的数："<<endl;
	cin >> a;
	
	BSTNode<int>* findnode = s.search(a);
	if(!findnode)
	{
		cout<<"查找失败"<<endl;
	}
	else
	{
		cout<<findnode->_key<<"查找成功"<<endl;
	}
}

void create(BSTree<int> &s)
{
	cout<<"请输入二叉树结点以构造二叉查找树："<<endl;
	getchar();
	
	while(cin.get() != '\n')
	{
		cin.unget();
		int a ;
		cin >> a;
		
		BSTNode<int>* findnode = s.search(a);
		if(findnode)
		{
			cout << a << "键值已存在！" << endl;
			continue; 
		}
		else
			s.insert(a);
	}
	cout << "中序遍历:" ;	
	s.inOrder();	
	cout << endl;		
}

void insert(BSTree<int> &s)
{
	int a ;
	cout << "请输入要插入的值：" << endl;
	cin >> a ;
		
	BSTNode<int>* findnode = s.search(a);
	if(findnode)
	{
		cout << "键值已存在！" << endl;
	}
	else
	{
		s.insert(a); 
		cout << "中序遍历:" ;	
		s.inOrder();	
	}

}
