#include<iostream>
#include<string>

#define STACKSIZE 25

using namespace std;

template <class E , class K >
class Node
{
	private:
		K key;
		Node * right_child , * left_child;
		E * theElement;
	public:
		Node (E * iElement)
			:right_child(0),left_child(0),theElement(iElement) 
		{
			theElement->getKey(key);
		}
		void getKey(K &oKey) { oKey = key;}
		E *getElement() { return theElement;}
		Node * getRight(){ return right_child;}
		Node * getLeft() { return left_child;}
		void setRight(Node *iNode) { right_child = iNode;}
		void setLeft(Node *iNode) { left_child = iNode;}	
};

template <class E , class K>
class Tree
{
	private:
		Node<E,K> * root ;
		//used by deleteNode function only
		Node<E,K> * find(K , Node<E,K> *&,char &);
		
	public:
		Tree()
			:root(0)
		{ }
		void insert(E *);
		bool deleteNode(K);
		E * find(K);
		Node<E,K> * getRoot();
		bool isEmpty();
};

class Association
{
	private:
		int key;//key can not be modified
		string value;
	public:
		Association(int iKey , string iValue)
			:key(iKey),value(iValue)
		{ }
		void getKey(int &oKey) { oKey = key; }
		string getValue() { return value; }
		void setValue(string iValue) { value = iValue; }
		//no setkey function because key cannot be modified
};

template<class E , class K>
class Stack
{
	private:
		int stackPtr;
		Node<E,K> * stack[STACKSIZE ];
	public:
		Stack()
			:stackPtr(-1)
		{ }
		bool is_empty() { return stackPtr>=0 ;}
		int getStackPtr() {return stackPtr;}
		Node<E,K> *pop() {return stack[stackPtr--];}
		Node<E,K> *getTop() {return stack[stackPtr];}
		Node<E,K> *getElement(int pos)
		{
			if(pos < 0 || pos > stackPtr)
				return 0;
			return stack[pos];
		}
		bool push(Node<E,K> * theNode)
		{
			if(stackPtr + 1 == STACKSIZE  )
				return false;
			stack[++stackPtr] = theNode ;
			return true;
		}
};

template <class E , class K>
class PreOrderItr
{
	private:
		Node<E,K> * root;
		Stack<E,K> * theStack;
	public:
		PreOrderItr()
			:root(0)
		{
			theStack = new Stack<E,K>();
		}
		bool init(Tree<E,K> *);
		bool operator++();
		bool operator!() { return theStack->is_empty(); }
		E * operator() ();	
};

class Dictionary
{
	private:
		string defaultValue;
		Tree<Association , int> * theTree;
		
	public:
		Dictionary();//sets default value
		Dictionary(string iDefault)
			:defaultValue(iDefault)
		{
			theTree = new Tree<Association , int>();
		}
		string operator[](int key)
		{
			Association * theAssociation = getAssociation(key);
			//if not already in the tree ,create an association for this key
			if(!theAssociation)
			{
				theAssociation = new Association(key , defaultValue);
				theTree->insert(theAssociation);
			}
			return theAssociation->getValue();
		} 
		void deleteAllValues()
		{
			PreOrderItr<Association , int> theItr;
			//traverse the tree
			Association * theAssociation;
			for(theItr.init(theTree) ; !theItr ; ++theItr)
			{
				theAssociation = theItr();
				if(theAssociation)
					theAssociation->setValue("/0") ;
			}
		}
		Association *getAssociation(int key) { return (theTree->find(key));}
		bool includedKey(int key) { return (getAssociation(key) != 0); }
		bool isEmpty() { return theTree->isEmpty();}
		bool removeKey(int key) { return (theTree->deleteNode(key));}
		//set a default value for new associations
		void setDefault(string iValue) { defaultValue = iValue ;}
		Tree<Association,int> * getTree() { return theTree ;}
};

template <class E , class K>
class InOrderItr
{
	private:
		Node<E,K> * root;
		void goLeft(Node<E,K> *node)
		{
			while(node)
			{
				theStack->push(node);
				node = node->getLeft();
			}
		}
		Stack<E,K> * theStack;
	public:
		InOrderItr()
			:root(0)
		{
			theStack = new Stack<E,K>();
		}
		bool init(Tree<E,K> *tree)
		{
			root = tree->getRoot(); 
			goLeft(root);
			return theStack->is_empty();
		}
		bool operator++();
		bool operator!() { return theStack->is_empty(); }
		E * operator()()
		{
			Node<E,K>* theNode = theStack->getTop();
			return theNode->getElement();
		}	
}; 

class DictionaryItr
{
	private:
		Dictionary * theDictionary;
		InOrderItr<Association , int> theItr;
	public:
		DictionaryItr(Dictionary *iDictionary)
			:theDictionary(iDictionary)
		{
			theItr.init(theDictionary->getTree());
		}
		Association * getNext()
		{
			Association * theAssociation = 0;
			if(!theItr)
			{
				theAssociation = theItr();
				++theItr;
			}
			return theAssociation;
		}
};

template <class E ,class K>
void Tree<E,K>::insert(E *theElement)
{
	Node<E,K> *current,*child,*newNode;
	
	K key;
	theElement->getKey(key); 
	
	if(root)
	{
		current = root ;
		while(current)
		{
			K currentKey;
			current->getKey(currentKey);
			if(currentKey < key)
			{
				child = current->getRight();
				if(!child)
				{
					newNode = 
						new Node<Association,int>(theElement);
					
					current->setRight(newNode);
					return;
				}
			}
			else
			{
				child = current->getLeft();
				if(!child)
				{
					newNode = 
						new Node<Association,int>(theElement);
					current->setLeft(newNode);
					return ;
				}
			}
			current = child;
		}
	}
	else
		root = new Node<Association,int> (theElement);	
}

template <class E ,class K>
bool Tree<E,K>::deleteNode(K key)
{
	Node<E,K> *previous = 0;//parent
	char direction ;
	Node<E,K> * theNode = find(key,previous ,direction);
	
	if(theNode == 0)
		return false;//Not found  
	E *theElement = theNode->getElement();	
	
	if(theNode->getRight()==0 && theNode->getLeft()==0 )
	{
		if(theNode == root )
			root = 0;
		else
			if(direction == 'r')
				previous->setRight(0);
			else
				previous->setLeft(0);
	}
	else if(theNode->getRight() != 0 && theNode->getLeft()==0)
	{
		Node<E,K> * subtree = theNode->getRight();
		if(theNode == root )
			root = subtree;
		else
		{
			if(direction == 'r')
				previous->setRight(subtree);
			else
				previous->setLeft(subtree);
		}
	}
	else if(theNode->getRight() == 0 && theNode->getLeft() !=0)
	{
		Node<E,K> * subtree = theNode->getLeft();
		if(theNode == root )
			root = subtree;
		else
		{
			if(direction == 'r')
				previous->setRight(subtree);
			else
				previous->setLeft(subtree);
		}
	}
	else
	{
		Node<E,K> * next;
		Node<E,K> * current = theNode->getLeft();
		//if there is a right subtree of left child
		if(current->getRight() != 0)
		{
			next = current->getRight();
			while(next->getRight() != 0)
			{
				current = next;
				next = current->getRight();
			} 
			//replace deleted node with node found
			current->setRight(next->getLeft());
			next->setLeft(theNode->getLeft());
			next->setRight(theNode->getRight());
			//set parent pointers
			if(theNode != root)
			{
				if(direction == 'l')
					previous->setLeft(next);
				else
					previous->setRight(next);
			}
			else
				root = next ;	
	    }
	    else //since no right subtree ,replace with left child
	    {
	    	next = current ;
	    	next->setRight(theNode->getRight());
	    	if(theNode != root)
	    		if(direction == 'l')
	    			previous->setLeft(next);
	    		else
	    			previous->setRight(next);
			else
				root = next ;
		}
	}
	
	delete theNode;
	return true;
}

template <class E ,class K>
Node<E,K>* Tree<E,K>::find(K key ,Node<E,K> *&previous , char &d)
{
	Node<E,K> *current ;
	
	if(root)
	{
		current = root ;
		previous = current ;
		while(current)
		{
			int currentKey;
			current->getKey(currentKey);
			if(currentKey == key)
				return current;
			if(currentKey < key)
			{
				previous = current ;
				d = 'r';
				current = current->getRight();
			}
			else
			{
				previous = current ;
				d = 'l';
				current = current->getLeft();
			}
		}
	}
	return 0;
}

template <class E ,class K>
E * Tree<E,K>::find(K key)
{
	Node<E,K> *current;
    
    if(root)
    {
    	current = root ;
		K currentKey;
		current->getKey(currentKey);
		while(current)
		{
			if( currentKey == key)
				return current->getElement();
			if( currentKey < key)
				current = current->getRight();
			else
			    current = current->getLeft();
			if(current)
				current->getKey(currentKey);
		} 
	}
	return 0;//not found 
}

template <class E ,class K>
bool PreOrderItr<E,K>::operator++()
{
	Node<E,K> * current = theStack->getTop();
	Node<E,K> * next = current->getLeft();
	bool found = false ;
	
	if(next)
	{
		theStack->push(next);
		found = true ;
	}
	else
	{
		while(theStack->is_empty())
		{
			current = theStack->pop();
			next = current->getRight();
			if(next)
			{
				theStack->push(next);
				found = true ;
			}
		}
	}
	
	return found;
}

template <class E ,class K>
E* PreOrderItr<E,K>::operator()()
{
	Node<E,K> * theNode = theStack->getTop();
	return theNode->getElement();
}

template <class E ,class K>
bool PreOrderItr<E,K>::init(Tree<E,K> * tree)
{
	root = tree->getRoot();
	if(root)
		theStack->push(root);
	return theStack->is_empty();
}

template <class E ,class K>
bool InOrderItr<E,K>::operator++()
{
	Node<E,K> * parent ,*child ;
	
	if(theStack->is_empty())
	{
		parent = theStack->pop();
		child = parent->getRight();
		if(child)
			goLeft(child); 
	}
	return theStack->is_empty();
}


class AppClass
{
	private:
		Dictionary * theTree;
		int simpleMenu();
		void addThing();
		void deleteThing();
		void findThing();
		void listThings();	
		
	public:
		AppClass()
		{
			
		}
		void run();
};


int main()
{
	AppClass * theApp = new AppClass();
	theApp->run();
	return 0;
}
