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
	private:
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
	private:
		Node *root ;
		Node *find(int ,Node *& ,char &);//used by deleteNode function
		functionPtr compareFunction;
	public:
		Tree(functionPtr iPtr)
			:root(0),compareFunction(iPtr)
		{ }
		int load();
		void write();
		void insert(Thing *);//source 
		int deleteNode(int );
		Thing * find(int );
		Node *getRoot() { return root ;}	
};

class AppClass
{
	private:
		Tree * theTree;
		int simpleMenu();
		void addThing();
		void deleteThing();
		void findThing();
		void listThings();	
		
	public:
		AppClass()
		{
			theTree = new Tree(&Thing::compare);
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

void Tree::insert(Thing *theThing)
{
	Node *current,*child,*newNode;
	
	int key;
	theThing->getKey(key); 
	
	if(root)
	{
		current = root ;
		while(current)
		{
			int currentKey;
			current->getKey(currentKey);
			if(currentKey < key)
			{
				child = current->getRight();
				if(!child)
				{
					newNode = new Node(theThing);
					
					if(!newNode)
					{
						cout << "\nCannot create Node.";
						return ;
					}
					current->setRight(newNode);
					return;
				}
			}
			else
			{
				child = current->getLeft();
				if(!child)
				{
					newNode = new Node(theThing);
					if(!newNode)
					{
						cout << "\nCannot create Node.";
						return ;
					}
					current->setLeft(newNode);
					return ;
				}
			}
			current = child;
		}
	}
	else
	{
		root = new Node(theThing);
		if(!root)
		{
			cout << "\nCannot create Node.";
			return ;
		}
	}	
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


int Tree::deleteNode(int key)
{
	Node *previous = 0;//parent
	char direction ;
	Node * theNode = find(key,previous ,direction);
	
	if(theNode == 0)
		return 0;//Not found  
	Thing *theThing = theNode->getThing();	
	
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
		Node * subtree = theNode->getRight();
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
		Node * subtree = theNode->getLeft();
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
		Node * next;
		Node * current = theNode->getLeft();
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
	
	delete theThing;
	delete theNode;
	return 1;
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
		 << "ID = " << current->getID()
		 << "Name = "<<current->getName()
		 <<endl; 
}

int main()
{
	AppClass * theApp = new AppClass();
	theApp->run();
	return 0;
} 
