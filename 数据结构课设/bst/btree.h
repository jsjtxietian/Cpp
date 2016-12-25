#ifndef _BINARY_SEARCH_TREE_
#define _BINARY_SEARCH_TREE_
#include <iostream>

using namespace std;
template<typename T>
//树结点结构
class BSTNode{
public:
	T _key; //关键在字（键值）
	BSTNode *_lchild; //左孩
	BSTNode *_rchild; //右孩
	BSTNode *_parent; // 双亲
	//构造函数
	BSTNode(T key ,BSTNode *lchild,BSTNode *rchild,BSTNode *parent):
	_key(key),_lchild(lchild),_rchild(rchild),_parent(parent){};
};

template<typename T>
class BSTree{
private:
	BSTNode<T> *_Root ;  //根结点
public:
	BSTree():_Root(NULL){};
	~BSTree(){};
	void insert (T key);//二叉树的插入

	BSTNode<T>* search (T key)  ;//二叉树的查找
	void preOrder()  ;  //先序输出
	void inOrder() ;   //中序输出
	void postOrder() ; //后序输出

	void print();//打印二叉树
	void remove(T key);
	void destory ();
	//内部使用函数，供外部接口调用
private:
	void insert(BSTNode<T>* &tree,BSTNode<T>* z);
	BSTNode<T>* search(BSTNode<T>* &tree,T key) const;
	void preOrder(BSTNode<T>*&tree) const;
	void inOrder(BSTNode<T>*&tree) const;
	void postOrder(BSTNode<T>*&tree) const;

	void print(BSTNode<T>*& tree);
	BSTNode<T>* remove(BSTNode<T>* &tree, BSTNode<T> *z);
	void destory(BSTNode<T>*& tree);
};

void search(BSTree<int>& s);
void create(BSTree<int> &s);
void insert(BSTree<int> &s);
/*
*插入操作
*非递归实现
*内部使用函数
*/
template<typename T>
void BSTree<T> ::insert(BSTNode<T>* &tree,BSTNode<T>* z)
{
	BSTNode<T>* parent = NULL;
	BSTNode<T>* temp = tree;
	//寻找插入点
	while(temp!=NULL)
	{
		parent= temp;
		if(z->_key>temp->_key)
			temp= temp->_rchild;
		else 
			temp=temp->_lchild;
	}
	z->_parent = parent;
	if(parent==NULL) //如果树本来就是空树，则直接把z节点插入根节点
		tree = z;
	else if(z->_key>parent->_key) //如果z的值大于其双亲，则z为其双亲的右孩
		parent->_rchild = z;
	else						  
		parent->_lchild = z;
}
/*
*
*接口
*/
template <typename T>
void BSTree<T>::insert(T key)
{
	//创建一个新的节点，使用构造函数初始化
	BSTNode<T>* z= new BSTNode<T>(key,NULL,NULL,NULL);
	if(!z) //如果创建失败则返回
		return ;
	//调用内部函数进行插入
	insert(_Root,z);
}
/*
*查找操作
*非递归实现
*内部使用函数
*/
template <typename T>
BSTNode<T>*  BSTree<T>::search(BSTNode<T>* &tree,T key) const
{
	BSTNode<T>* temp = tree;
	while(temp != NULL)
	{
		if(temp->_key == key)
			return temp;
		else if(temp->_key>key)
			temp = temp->_lchild;
		else
			temp = temp->_rchild;
	}
	return NULL;
}

/*
*接口
*/
template <typename T>
BSTNode<T> * BSTree<T>::search(T key) 
{
	return search(_Root,key);
}
/*
*
*前序遍历算法
*外部使用接口
*
*/
template<typename T>
void BSTree<T>::preOrder(BSTNode<T>*&tree) const
{
	if(tree)
	{
		cout<<tree->_key<<" ";
		preOrder(tree->_lchild);
		preOrder(tree->_rchild);
	}
}
template <typename T>
void BSTree<T>::inOrder(BSTNode<T>*&tree) const
{
	if(tree)
	{
		inOrder(tree->_lchild);
		cout<<tree->_key<<" ";
		inOrder(tree->_rchild);
	}
}
template <typename T>
void BSTree<T>::postOrder(BSTNode<T>*&tree) const
{
	if(tree)
	{
		postOrder(tree->_lchild);
		postOrder(tree->_rchild);
		cout<<tree->_key<<" ";
	}
}
/*
*遍历算法
*分别为前序、中序、后序
*BSTree 类外部接口函数
*
*/
template<typename T>
void BSTree<T>::preOrder()
{
	preOrder(_Root);
}
template<typename T>
void BSTree<T>::inOrder()
{
	inOrder(_Root);
}
template<typename T>
void BSTree<T>::postOrder()
{
	postOrder(_Root);
}

/*
*
*打印函数
*打印出平衡二叉树
*BStree内部函数
*/
template<typename T>
void BSTree<T>::print(BSTNode<T>*& tree)
{
	if(tree) //如果tree不为空
	{
		if(tree->_lchild) //结点有左孩子
		{
			cout<<"节点"<<tree->_key<<"有左孩子为"<<tree->_lchild->_key<<endl;
		}
		else 
			cout<<"节点"<<tree->_key<<"无左孩子"<<endl;
		if(tree->_rchild)
		{
			cout<<"节点"<<tree->_key<<"有右孩子为"<<tree->_rchild->_key<<endl;
		}
		else 
			cout<<"节点"<<tree->_key<<"无右孩子"<<endl;
		print(tree->_lchild);
		print(tree->_rchild);
	}
}
/*
*接口
*/
template<typename T>
void BSTree<T>::print()
{
	print(_Root);
}

/*
*
*删除结点
*BSTree类内部调用函数
*
*/
template <class T>
BSTNode<T>* BSTree<T>::remove(BSTNode<T>* &tree, BSTNode<T> *z)
{
	BSTNode<T> *x=NULL;
	BSTNode<T> *y=NULL;
	if ((z->_lchild == NULL) || (z->_rchild == NULL) )
		y = z;
	else
		y = sucessor(z);
	if (y->_lchild != NULL)
		x = y->_lchild;
	else
		x = y->_rchild;
	if (x != NULL)
		x->_parent = y->_parent;
	if (y->_parent == NULL)
		tree = x;
	else if (y == y->_parent->_lchild)
		y->_parent->_lchild = x;
	else
		y->_parent->_rchild= x;
	if (y != z) 
		z->_key = y->_key;
	return y;
}
/*
* 接口
*/
template<typename T>
void BSTree<T>::remove(T key)
{
	BSTNode<T> *z, *node; 
	if ((z = search(_Root, key)) != NULL)
		if ( (node = remove(_Root, z)) != NULL)
			delete node;
}
/*
*
*销毁查找二叉树
*内部调用函数
*
*/
template<typename T>
void BSTree<T>::destory(BSTNode<T>*& tree)
{
	if(tree->_lchild!=NULL)
		destory(tree->_lchild);
	if(tree->_rchild!=NULL)
		destory(tree->_rchild);
	if(tree->_lchild==NULL&&tree->_rchild==NULL)
	{
		delete(tree);
		tree = NULL;
	}
}
/*
*接口
*/
template<typename T>
void BSTree<T>::destory()
{
	destory(_Root);
}
#endif
