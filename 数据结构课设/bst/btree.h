#ifndef _BINARY_SEARCH_TREE_
#define _BINARY_SEARCH_TREE_
#include <iostream>

using namespace std;
template<typename T>
//�����ṹ
class BSTNode{
public:
	T _key; //�ؼ����֣���ֵ��
	BSTNode *_lchild; //��
	BSTNode *_rchild; //�Һ�
	BSTNode *_parent; // ˫��
	//���캯��
	BSTNode(T key ,BSTNode *lchild,BSTNode *rchild,BSTNode *parent):
	_key(key),_lchild(lchild),_rchild(rchild),_parent(parent){};
};

template<typename T>
class BSTree{
private:
	BSTNode<T> *_Root ;  //�����
public:
	BSTree():_Root(NULL){};
	~BSTree(){};
	void insert (T key);//�������Ĳ���

	BSTNode<T>* search (T key)  ;//�������Ĳ���
	void preOrder()  ;  //�������
	void inOrder() ;   //�������
	void postOrder() ; //�������

	void print();//��ӡ������
	void remove(T key);
	void destory ();
	//�ڲ�ʹ�ú��������ⲿ�ӿڵ���
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
*�������
*�ǵݹ�ʵ��
*�ڲ�ʹ�ú���
*/
template<typename T>
void BSTree<T> ::insert(BSTNode<T>* &tree,BSTNode<T>* z)
{
	BSTNode<T>* parent = NULL;
	BSTNode<T>* temp = tree;
	//Ѱ�Ҳ����
	while(temp!=NULL)
	{
		parent= temp;
		if(z->_key>temp->_key)
			temp= temp->_rchild;
		else 
			temp=temp->_lchild;
	}
	z->_parent = parent;
	if(parent==NULL) //������������ǿ�������ֱ�Ӱ�z�ڵ������ڵ�
		tree = z;
	else if(z->_key>parent->_key) //���z��ֵ������˫�ף���zΪ��˫�׵��Һ�
		parent->_rchild = z;
	else						  
		parent->_lchild = z;
}
/*
*
*�ӿ�
*/
template <typename T>
void BSTree<T>::insert(T key)
{
	//����һ���µĽڵ㣬ʹ�ù��캯����ʼ��
	BSTNode<T>* z= new BSTNode<T>(key,NULL,NULL,NULL);
	if(!z) //�������ʧ���򷵻�
		return ;
	//�����ڲ��������в���
	insert(_Root,z);
}
/*
*���Ҳ���
*�ǵݹ�ʵ��
*�ڲ�ʹ�ú���
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
*�ӿ�
*/
template <typename T>
BSTNode<T> * BSTree<T>::search(T key) 
{
	return search(_Root,key);
}
/*
*
*ǰ������㷨
*�ⲿʹ�ýӿ�
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
*�����㷨
*�ֱ�Ϊǰ�����򡢺���
*BSTree ���ⲿ�ӿں���
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
*��ӡ����
*��ӡ��ƽ�������
*BStree�ڲ�����
*/
template<typename T>
void BSTree<T>::print(BSTNode<T>*& tree)
{
	if(tree) //���tree��Ϊ��
	{
		if(tree->_lchild) //���������
		{
			cout<<"�ڵ�"<<tree->_key<<"������Ϊ"<<tree->_lchild->_key<<endl;
		}
		else 
			cout<<"�ڵ�"<<tree->_key<<"������"<<endl;
		if(tree->_rchild)
		{
			cout<<"�ڵ�"<<tree->_key<<"���Һ���Ϊ"<<tree->_rchild->_key<<endl;
		}
		else 
			cout<<"�ڵ�"<<tree->_key<<"���Һ���"<<endl;
		print(tree->_lchild);
		print(tree->_rchild);
	}
}
/*
*�ӿ�
*/
template<typename T>
void BSTree<T>::print()
{
	print(_Root);
}

/*
*
*ɾ�����
*BSTree���ڲ����ú���
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
* �ӿ�
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
*���ٲ��Ҷ�����
*�ڲ����ú���
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
*�ӿ�
*/
template<typename T>
void BSTree<T>::destory()
{
	destory(_Root);
}
#endif
