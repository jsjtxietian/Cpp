#include<iostream>
#include<fstream>

#define STACKSIZE 25

using namespace std;

class Treeable
{
	public:
		Treeable() { }
		virtual void getKey(int &) = 0;
};

class Thing : public Treeable
{
	public:
		Thing() { }
		Thing(int iID,string iName)
			:thing_id(iID) , thing_name(iName)
		{ }
		
		int    getID() const  { return thing_id ;}
		string getName()   const { return thing_name ;}
	    void   getKey(int &key)  { key = thing_id; }
		int    compare(int );
		void   write(ostream & = cout );
		
	private:
		int thing_id;
		string thing_name;
}; 

typedef int (Thing::*functionPtr) (int);

class Node
{
	protected:
		int key;
		Node *right_child;
		Node *left_child;
		Thing * theThing;
	public:
		Node(Thing *iThing)
			:theThing(iThing),right_child(0),left_child(0)
		{
			theThing->getKey(key);
		}
		void getKey(int &theKey)     { theKey = key ;}
		Thing *getThing()            { return theThing ;}
		Node * getRight()            { return right_child ;}
		Node * getLeft()             { return left_child ;}
		void   setLeft(Node *iNode)  { left_child = iNode ;}
		void   setRight(Node *iNode) { right_child = iNode ;}	
};

class AVLNode : public Node
{
	private:
		int balanceFactor;
		AVLNode *singleRotateLeft();
		AVLNode *singleRotateRight();
		AVLNode *restoreLeftBalance(int );
		AVLNode *restoreRightBalance(int );
		AVLNode *balance();
		AVLNode *removeLeftChild(AVLNode * &);
	public:
		AVLNode(Thing *iThing)
			:Node(iThing),balanceFactor(0) //I changed here
		{ }
		void setLeft(AVLNode *lchild) { left_child = lchild ;}
		void setRight(AVLNode *rchild) { right_child = rchild ;}
		AVLNode * getLeft()     { return (AVLNode *)left_child ;}
		AVLNode * getRight()    { return (AVLNode *)right_child ;}
		int getBalanceFactor()  { return balanceFactor;}
		void setBalanceFactor(int BF) { balanceFactor = BF ;}
		AVLNode * insert(Thing *);
		AVLNode * deleteNode(int ,AVLNode *&); 
}; 

class Stack
{
	private:
		int stackPtr;
		Node * stack[STACKSIZE ];
	public:
		Stack()
			:stackPtr(-1)
		{ }
		int is_empty() { return stackPtr>=0 ;}
		int getStackPtr() {return stackPtr;}
		Node *pop() {return stack[stackPtr--];}
		Node *getTop() {return stack[stackPtr];}
		Node *getElement(int pos)
		{
			if(pos < 0 || pos > stackPtr)
				return 0;
			return stack[pos];
		}
		bool push(Node * theNode)
		{
			if(stackPtr + 1 == STACKSIZE  )
				return false;
			stack[++stackPtr] = theNode ;
			return true;
		}
};

class Tree
{
	protected:
		Node *root ;
		Node *find(int ,Node *& ,char &);//used by deleteNode function
		functionPtr compareFunction;
	public:
		Tree(functionPtr iPtr)
			:root(0),compareFunction(iPtr)
		{ }
		void write();
		Thing * find(int );
		Node *getRoot() { return root ;}	
};

class AVLTree : public Tree
{
	public:
		AVLTree(functionPtr iPtr)
			:Tree(iPtr)
		{ }
		void insert(Thing *);
		bool deleteNode(int );
}; 

class AppClass
{
	private:
		AVLTree * theTree;
		int simpleMenu();
		void addThing();
		void deleteThing();
		void findThing();
		void listThings();	
		
	public:
		AppClass()
		{
			theTree = new AVLTree(&Thing::compare);
		}
		void run();
};


class InOrderItr
{
	private:
		Node * root;
		void goLeft(Node *);
		Stack * theStack;
	public:
		InOrderItr()
			:root(0)
		{
			theStack = new Stack();
		}
		int init(Tree *);
		int operator++();
		int operator!() { return theStack->is_empty(); }
		Thing * operator()();	
}; 

class PreOrderItr
{
	private:
		Node * root;
		Stack * theStack;
	public:
		PreOrderItr()
			:root(0)
		{
			theStack = new Stack();
		}
		int init(Tree *);
		int operator++();
		int operator!() { return theStack->is_empty(); }
		Thing * operator()();	
};

bool AVLTree::deleteNode(int key)
{
	AVLNode * deletedNode = 0;
	AVLNode * theRoot = (AVLNode *) root;
	
	if(theRoot)
		root = theRoot->deleteNode(key,deletedNode);
		
	if(deletedNode)
	{
		delete deletedNode;
		return true;
	}
	else
		return false;
}

void AVLTree::insert(Thing *theThing)
{
	AVLNode * theRoot = (AVLNode *) root;
	if(theRoot)
		root = theRoot->insert(theThing);
	else
		root = new AVLNode(theThing);
}

AVLNode* AVLNode::insert(Thing *theThing)
{
	//handle keys this way to make it type indepentent 
	//when implemented sa a template
	int newKey,currentKey;
	theThing->getKey(newKey);
	getKey(currentKey);
	
	AVLNode * left = (AVLNode *)left_child;
	AVLNode * right = (AVLNode *)right_child;
	
	if(newKey < currentKey) //insert into left subtree
	{
		if(left)//if there is a left child
		{
			int oldBF = left->getBalanceFactor();
			setLeft(left->insert(theThing));
			//determine whether tree is larger
			if( (left->getBalanceFactor() != oldBF)
			  && left->getBalanceFactor() )
			  balanceFactor--;
		}
		else
		{
			setLeft(new AVLNode(theThing));
			balanceFactor--;
		}
	}
	else //insert into right subtree
	{
		if(right)//if there is a right child
		{
			int oldBF = right->getBalanceFactor();
			setRight(right->insert(theThing));
			//determine whether tree is larger
			if( (right->getBalanceFactor() != oldBF)
			  && right->getBalanceFactor() )
			  balanceFactor++;
		}
		else
		{
			setRight(new AVLNode(theThing));
			balanceFactor++;
		}
	}
	//determine whether tree is balanced
	if( balanceFactor < -1 || balanceFactor >1 )
		return balance();
	return this;  
}

AVLNode * AVLNode::balance()
{
	AVLNode * left = (AVLNode *)left_child;
	AVLNode * right = (AVLNode *)right_child;
	if(balanceFactor < 0)
	{
		if(left->getBalanceFactor() <= 0)
			return singleRotateRight();
		else
		{
			setLeft(left->singleRotateLeft());
			return singleRotateRight();
		}
	}
	else
	{
		if(right->getBalanceFactor() >= 0)
			return singleRotateLeft();
		else
		{
			setRight(right->singleRotateRight());
			return singleRotateLeft();
		}
	}	
}

AVLNode * AVLNode::singleRotateRight()
{
	AVLNode * current = this ;
	AVLNode * child = (AVLNode *)left_child;
	
	//perform the rotation
	current->setLeft(child->getRight());
	child->setRight(current);
	//recompute balance factors
	int currentBF = current->balanceFactor;
	int childBF = child->getBalanceFactor();
	if(childBF <= 0)
	{
		if(childBF > currentBF )
			child->setBalanceFactor(childBF + 1);
		else
			child->setBalanceFactor(currentBF + 2);
		current->balanceFactor = 1 + currentBF - childBF;
	}
	else
	{
		if(currentBF <= -1)
			child->setBalanceFactor(childBF + 1);
		else
			child->setBalanceFactor(childBF + currentBF + 2 );
		current->balanceFactor = 1 + currentBF ;
	}
	return child;
}

AVLNode * AVLNode::singleRotateLeft()
{
	AVLNode * current = this ;
	AVLNode * child = (AVLNode *)right_child;
	
	//perform the rotation
	current->setRight(child->getLeft());
	child->setLeft(current);
	//recompute balance factors
	int currentBF = current->balanceFactor;
	int childBF = child->getBalanceFactor();
	if(childBF <= 0)
	{
		if(childBF >= 1)
			child->setBalanceFactor(childBF - 1);
		else
			child->setBalanceFactor(currentBF + childBF - 2);
		current->balanceFactor = currentBF - 1;
	}
	else
	{
		if(currentBF <= childBF )
			child->setBalanceFactor(currentBF - 2 );
		else
			child->setBalanceFactor(childBF - 1 );
		current->balanceFactor = (currentBF - childBF ) - 1;
	}
	return child;
}

AVLNode * AVLNode::
deleteNode(int newKey , AVLNode * & deletedNode)
{
	AVLNode * right = (AVLNode *)right_child;
	AVLNode * left  = (AVLNode *)left_child;
	
	if(key == newKey)
	{
		deletedNode = this ;
		if(!right)
			return left;
		int oldBF = right->getBalanceFactor();
		AVLNode * newRoot;
		setRight(right->removeLeftChild(newRoot) );
		newRoot->setLeft( (AVLNode *)left_child ); 
		newRoot->setRight( (AVLNode *)right_child );
		newRoot->setBalanceFactor(balanceFactor);
		return newRoot->restoreRightBalance(oldBF);  
	}
	else if( newKey < key)
	{
		if(!left)
			return this;
		
		int oldBF = left->getBalanceFactor();
		setLeft(left->deleteNode(key,deletedNode));
		return restoreLeftBalance(oldBF);
	}
	else
	{
		if(!right)
			return this;
		
		int oldBF = right->getBalanceFactor();
		setRight(right->deleteNode(key,deletedNode));
		return restoreRightBalance(oldBF);
	}
} 

AVLNode * AVLNode::removeLeftChild(AVLNode *&childNode)
{
	AVLNode * left = (AVLNode *) left_child;
	if(!left)
	{
		childNode = this;
		return (AVLNode *)right_child;
	}
	
	int oldBF = left->getBalanceFactor();
	setLeft(left->removeLeftChild(childNode));
	return restoreLeftBalance(oldBF);
}

AVLNode * AVLNode::restoreRightBalance(int oldBF)
{
	AVLNode * right = (AVLNode *)right_child;
	
	if(!right)
		balanceFactor--;
	else
		if( (right->getBalanceFactor() != oldBF)
		   && (right->getBalanceFactor() == 0))
		   balanceFactor--;
	
	if(balanceFactor < -1)
		return balance();
	return this;
}

AVLNode * AVLNode::restoreLeftBalance(int oldBF)
{
	AVLNode * left = (AVLNode *)left_child;
	
	if(!left)
		balanceFactor++;
	else
		if( (left->getBalanceFactor() != oldBF)
		   && (left->getBalanceFactor() == 0))
		   balanceFactor++;
	
	if(balanceFactor > 1)
		return balance();
	return this;
}

int PreOrderItr::operator++()
{
	Node * current = theStack->getTop();
	Node * next = current->getLeft();
	
	if(next)
	{
		theStack->push(next);
		return 1;
	}
	
	while(theStack->is_empty())
	{
		current = theStack->pop();
		next = current->getRight();
		if(next)
		{
			theStack->push(next);
			return 1;
		}
	}
	return 0;
}

void InOrderItr::goLeft(Node *node)
{
	while(node)
	{
		theStack->push(node);
		node = node->getLeft();
	}
}

int InOrderItr::operator++()
{
	Node * parent ,*child ;
	
	if(theStack->is_empty())
	{
		parent = theStack->pop();
		child = parent->getRight();
		if(child)
			goLeft(child); 
	}
	return theStack->is_empty();
}

Thing * InOrderItr::operator()()
{
	Node * theNode = theStack->getTop();
	return theNode->getThing();
}

Thing * PreOrderItr::operator()()
{
	Node * theNode = theStack->getTop();
	return theNode->getThing();
}

int Thing::compare(int key)
{
	int result;
	if(thing_id == key)
		result = 0;
	else if(thing_id > key)
	    result = 1;
	else
		result = -1;
	return result;
}

int InOrderItr::init(Tree * tree)
{
	root = tree->getRoot();
	goLeft(root);
	return theStack->is_empty();
}

int PreOrderItr::init(Tree * tree)
{
	root = tree->getRoot();
	if(root)
		theStack->push(root);
	return theStack->is_empty();
}

void Thing::write(ostream & os)
{
	os << "ID = " <<thing_id << ' '
	   << "Name = " << thing_name << endl;
}



Thing * Tree::find(int key)
{
	Node *current;
	Thing * currentThing;
    
    if(root)
    {
    	current = root ;
		
		while(current)
		{
			currentThing = current->getThing();
			if( (currentThing->*compareFunction)(key) == 0)
				return current->getThing();
			if( (currentThing->*compareFunction)(key) < 0)
				current = current->getRight();
			else
			    current = current->getLeft();
		} 
	}
	return 0;//not found 
}


Node* Tree::find(int key ,Node *&previous , char &d)
{
	Node *current ;
	
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

void AppClass::listThings()
{
	InOrderItr theItr;
	Thing * theThing;
	for(theItr.init(theTree) ; !theItr ; ++theItr)
	{
		theThing = theItr();
		cout << "ID = "<< theThing->getID() 
			 << "; Name = "<<theThing->getName()
			 << "." << endl;
	}
	theTree->write();//!!!I change here~
}

void Tree::write()
{
	ofstream fout("things.txt");
	if(!fout.is_open())
	{
		cerr<<"open files failed!";
		return ;
	}
	PreOrderItr theItr;
	
	Thing * theThing;
	for(theItr.init(this); !theItr; ++theItr)
	{
		theThing = theItr();
		theThing->write(fout);
	}
}

void AppClass::run()
{
	int choice ;
	
	while( (choice = simpleMenu()) != 9)
	{
		switch(choice)
		{
			case 1:
				addThing();
				break;
			case 2:
				deleteThing();
				break;
			case 3:
				findThing();
				break;
			case 4:
				listThings();
			case 9:
				break;
			default:
				cout << "Unreconignized menu option ." << endl;
		}
	}
}

int AppClass::simpleMenu()
{
	int choice;
	cout <<"\nYou can: "
		 <<"\n 1.Add an item"
		 <<"\n 2.Delete an item"
		 <<"\n 3.Find elements"
		 <<"\n 4.List elements"
		 <<"\n 9.Quit"
		 <<"\n\n"
		 <<"Choice: ";
	cin>>choice;
	return choice;
}

void AppClass::addThing()
{
	Thing * newThing;
	int ID;
	string name ;
	cout << "\nID:";
	cin>>ID;
	cin.get();
	cout<<"Name: ";
	cin>>name;
	
	newThing = new Thing(ID,name);
	theTree->insert(newThing);
}

void AppClass::deleteThing()
{
	int ID;
	cout << "ID to remove:";
	cin>>ID;
	bool result = theTree->deleteNode(ID);
	if(result==1)
	{
		cout << "succeed!\n";
	}
	else
	{
		cout << "failed!\n";
	}
}

void AppClass::findThing()
{
	int ID;
	cout << "ID to find:";
	cin>>ID;
	Thing *current = theTree->find(ID);
	if(current == 0)
	{
		cout<<"failed!"<<endl;
		return ;
	}
	
	cout << "Find the Thing!\n"
		 << "ID = " << current->getID() <<' ' 
		 << "Name = "<<current->getName()
		 <<endl; 
}

int main()
{
	AppClass * theApp = new AppClass();
	theApp->run();
	return 0;
} 
