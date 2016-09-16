#include<iostream>
#include<string>

#define MAX 4
#define MIN 2

using namespace std;

class BTreeable
{
	public:
		BTreeable() { }
		virtual void getKey(int &) = 0;
};

class Thing : public BTreeable
{
	public:
		Thing() { }
		Thing(int iID,string iName)
			:thing_id(iID) , thing_name(iName)
		{ }
		
		int    getID() const  { return thing_id ;}
		string getName()   const { return thing_name ;}
	    void   getKey(int &key)  { key = thing_id; }
	private:
		int thing_id;
		string thing_name;
}; 

class BNode
{
	private:
		int numbElements;
		BNode * branches[MAX+1];
		//elements[0] is not used
		Thing * elements[MAX+1];
		//use getKey() to retrieve keys
	public:
		BNode()
			:numbElements(0)
		{
			for(int i = 0 ; i <= MAX ; i++ )
				branches[i] = 0;
			for(int i = 0 ; i < MAX ; i++ )
				elements[i] = 0;
		}
		
		int     getNumbElements()                  { return numbElements;}
		Thing * getElement(int index)              { return elements[index];}
		BNode * getBranch(int index)               { return branches[index];}
		
		void setNumbElements(int value)            { numbElements = value;}
		void setBranch(int index,BNode *theNode)   { branches[index] = theNode;}
		void setElement(int index,Thing *theThing) { elements[index] = theThing;}
		int  getKey(int index)//get keys for a specified Thing object
		{
			int key;
			elements[index]->getKey(key);
			return key;
		}
};

class BTree
{
	private:
		BNode * root ;
		//used by find function
		bool search(int ,BNode *,BNode *&,int &);
		bool searchNode(int ,BNode * ,int &);
		//used bby insert function
		bool pushDown(Thing *,BNode *,Thing *&, BNode *&);
		void pushIn(Thing *,BNode * ,BNode * ,int);
		void spilt(Thing *,BNode *, BNode * ,int ,Thing *&, BNode *&);
		//used by leleteElement function
		bool recursiveDelete(int ,BNode *);
		void remove(BNode * ,int);
		void successor(BNode * ,int);
		void restore(BNode * ,int );
		void moveRight(BNode * ,int );
		void moveLeft(BNode * ,int );
		void combine(BNode * ,int );
		
	public:
		BTree() 
			:root(0)
		{ }
		void insert(Thing *);//initiate an insertion
		Thing * find(int );//initiate a search
		
		bool isEmpty();
		bool deleteElement(int );//initiate a deletion	
};

class AppClass
{
	private:
		BTree * theTree;
		int simpleMenu();
		void addThing();
		void deleteThing();
		void findThing();
		
	public:
		AppClass()
		{
			theTree = new BTree();
		}
		void run();
};

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
			case 9:
				break;
			default:
				cout << "Unreconignized menu option ." << endl;
		}
	}
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
	bool result = theTree->deleteElement(ID);
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

int AppClass::simpleMenu()
{
	int choice;
	cout <<"\nYou can: "
		 <<"\n 1.Add an item"
		 <<"\n 2.Delete an item"
		 <<"\n 3.Find elements"
		 <<"\n 9.Quit"
		 <<"\n\n"
		 <<"Choice: ";
	cin>>choice;
	return choice;
}

Thing * BTree::find(int key)
{
	//start search
	BNode * foundNode = 0;
	int position;
	bool found = search(key,root,foundNode ,position);
	//hanle result
	if(found)
		return foundNode->getElement(position);
	else
		return 0;
}

bool BTree::search(int key,BNode * currentNode ,
					BNode *&foundNode ,int & position)
{
	bool found;
	if(currentNode == 0)
		found = false;
	else
	{
		found = searchNode(key , currentNode , position);
		if(found)
			foundNode = currentNode ;
		else
			found = search(key , currentNode->getBranch(position),
			              foundNode , position);
	}
	return found;
}

//sequential search of a single node
bool BTree::searchNode(int key ,BNode * currentNode ,int &position)
{
	bool found = false ;
	if(key < currentNode->getKey(1))
		position = 0;
	else
	{
		position = currentNode->getNumbElements();
		while(key < currentNode->getKey(position) && position > 1)
			position--;
		found = (key == currentNode->getKey(position));
	}
	return found;
}

void BTree::insert(Thing * newThing)
{
	BNode * rightSubtree;
	Thing * insertedThing;
	bool pushUp = pushDown(newThing , root ,
	                      insertedThing ,rightSubtree);
	if(pushUp)
	{
		BNode * newNode = new BNode();
		newNode->setNumbElements(1);
		newNode->setElement(1,insertedThing);
		newNode->setBranch(0,root);
		newNode->setBranch(1,rightSubtree);
		root = newNode ;
	}
}

bool BTree::pushDown(Thing * newThing ,BNode *currentNode,
                    Thing *& insertedThing, BNode *& rightSubtree)
{
	int position;
	bool found ,pushUp;
	if(currentNode == 0)
	{
		pushUp = true;
		insertedThing = newThing;
		rightSubtree = 0;
	}
	else
	{	
		int key;
		newThing->getKey(key); 
		found = searchNode(key , currentNode ,position);
		if(found)
			cout << "\nWarning:Inserting diplicate key .";
		pushUp = pushDown(newThing,currentNode->getBranch(position),
		                 insertedThing , rightSubtree);
		if(pushUp)
		{
			if(currentNode->getNumbElements() < MAX )
			{
				pushUp = false ;
				pushIn(insertedThing ,rightSubtree,
				      currentNode, position );
			}
			else
			{
				pushUp = true;
				spilt(newThing ,rightSubtree,currentNode,
					position,insertedThing , rightSubtree);
			}
		}
	}
	return pushUp;
}

void BTree::pushIn(Thing *newThing ,BNode * rightSubtree,
				    BNode *currentNode , int  position )
{
	int elements = currentNode->getNumbElements();
	int i;
	for(i = elements ; i >= position + 1 ; i--)
	{
		currentNode->setElement(i+1 , currentNode->getElement(i) );
		currentNode->setBranch(i+1 , currentNode->getBranch(i) );
	}
	currentNode->setElement(position + 1 , newThing );
	currentNode->setBranch(position + 1 , rightSubtree );
	currentNode->setNumbElements( elements + 1 );
}

void BTree::spilt(Thing *newThing , BNode *rightSubtree,
					BNode *currentNode , int position,
					Thing *& medianThing , BNode *& newRightSubtree)
{
	int median;
	
	if(position <= MIN)
		median = MIN;
	else
		median = MIN + 1;
	newRightSubtree = new BNode();
	for(int i = median + 1 ; i <= MAX ; ++i)
	{
		newRightSubtree->
			setElement( i - median , currentNode->getElement(i));
		newRightSubtree->
			setBranch( i - median , currentNode->getBranch(i));
	} 
	newRightSubtree->setNumbElements(MAX - median);
	currentNode->setNumbElements(median);
	if(position <= MIN)
		pushIn(newThing , rightSubtree ,currentNode ,position);
	else
		pushIn(newThing , rightSubtree , newRightSubtree , position - median);
	int elements = currentNode->getNumbElements();
	medianThing = currentNode->getElement(elements);
	newRightSubtree->setBranch(0 , currentNode->getBranch(elements));
	currentNode->setNumbElements(elements - 1 );
}

bool BTree::deleteElement(int key)
{
	bool found;
	found = recursiveDelete(key,root);
	if(found && root->getNumbElements() == 0)
		root = root->getBranch(0);
	return found;
} 

bool BTree::recursiveDelete(int key ,BNode * currentNode)
{
	int position;
	bool found;
	
	if(currentNode == 0)
		found = false;
	else
	{
		found = searchNode(key , currentNode ,position);
		if(found)
		{
			if(currentNode->getBranch(position-1) == 0)
				remove(currentNode,position);
			else
			{
				successor(currentNode,position);
				found = recursiveDelete
						(currentNode->getKey(position),
						 currentNode->getBranch(position));
			}
		}
		else
		{
			found = recursiveDelete
					(key , currentNode->getBranch(position));
		}
		BNode *branchNode = currentNode->getBranch(position);
		if(branchNode != 0 && branchNode->getNumbElements()<MIN)
			restore(currentNode , position);
	}
	return found;
}

void BTree::remove(BNode * currentNode ,int position)
{
	for(int i = position + 1 ; i <= currentNode->getNumbElements(); i++)
	{
		currentNode->setElement(i-1,currentNode->getElement(i));
		currentNode->setBranch(i-1,currentNode->getBranch(i));
	}
}

void BTree::successor(BNode * currentNode ,int position)
{
	BNode * branchNode = currentNode->getBranch(position);
	while(branchNode->getBranch(0) != 0)
		branchNode = branchNode->getBranch(0);
	currentNode->setElement(position,branchNode->getElement(1));
}

void BTree::restore(BNode * currentNode ,int position)
{
	if(position == 0)//leftmost element
	{
		BNode * branchNode = currentNode->getBranch(1);
		if(branchNode->getNumbElements() > MIN)
			moveLeft(currentNode , 1);
		else
			combine(currentNode , 1);
	}
	//rightmost element
	else if (position == currentNode->getNumbElements())
	{
		BNode * branchNode = currentNode->getBranch(position - 1);
		if(branchNode->getNumbElements() > MIN)
			moveRight(currentNode , position);
		else
			combine(currentNode , position);
	}
	else//middle elements
	{
		BNode * branchNode = currentNode->getBranch(position - 1 );
		if(branchNode->getNumbElements() > MIN)
			moveRight(currentNode , position);
		else
		{
			BNode * branchNode = currentNode->getBranch(position + 1 );
			if(branchNode->getNumbElements() > MIN)
				moveLeft(currentNode , position + 1);
			else
				combine(currentNode , position);
		}
	}
}

void BTree::moveLeft(BNode * currentNode , int position)
{
	BNode * branchNode = currentNode->getBranch(position - 1 );
	branchNode->setNumbElements(branchNode->getNumbElements() + 1);
	branchNode->setElement(branchNode->getNumbElements() ,
	                       currentNode->getElement(position));
	BNode * branchNode2 = currentNode->getBranch(position);
	branchNode->setBranch(branchNode->getNumbElements(),
	                      branchNode2->getBranch(0));
	currentNode->setElement(position,
							branchNode2->getElement(1));
	branchNode2->setBranch( 0 , branchNode2->getBranch(1));
	branchNode2->setNumbElements
						(branchNode2->getNumbElements() - 1);
	for(int i = 1 ; i <= branchNode2->getNumbElements(); i++)
	{
		branchNode2->setElement(i,branchNode2->getElement(i+1));
		branchNode2->setBranch(i, branchNode2->getBranch(i+1));
	}
}

void BTree::moveRight(BNode * currentNode , int position)
{
	BNode * branchNode = currentNode->getBranch(position);
	for(int i = branchNode->getNumbElements() ; i >= 1 ; i--)
	{
		branchNode->setElement(i+1 , branchNode->getElement(i));
		branchNode->setBranch(i+1 , branchNode->getBranch(i));
	}
	branchNode->setBranch(1 , branchNode->getBranch(0));
	branchNode->setNumbElements(branchNode->getNumbElements() + 1);
	branchNode->setElement( 1 , currentNode->getElement(position));
	
	BNode * branchNode2 = currentNode->getBranch(position - 1);
	currentNode->setElement(position,
				branchNode2->getElement(branchNode2->getNumbElements()));
	
	branchNode->setBranch( 0 , 
	                branchNode2->getBranch(branchNode2->getNumbElements()));
	
	branchNode2->setNumbElements
						(branchNode2->getNumbElements() - 1);
}

void BTree::combine(BNode * currentNode , int position)
{
	BNode * branchNode = currentNode->getBranch(position );
	BNode * branchNode2 = currentNode->getBranch(position - 1);
	
	branchNode2->setNumbElements
		(branchNode2->getNumbElements() + 1);
	branchNode2->setElement(branchNode2->getNumbElements(),
		currentNode->getElement(position) );
	branchNode2->setBranch
		(branchNode2->getNumbElements(),
		branchNode->getBranch(0));
	for(int i = 1 ; i <= branchNode->getNumbElements(); i++)
	{
		branchNode2->setNumbElements
	 		(branchNode2->getNumbElements() + 1);
     	branchNode2->setElement(branchNode2->getNumbElements(),
			branchNode->getElement(i) );
    	branchNode2->setBranch
			(branchNode2->getNumbElements(),
			branchNode->getBranch(i));
	}
	for(int i = position ; i <= currentNode->getNumbElements() - 1 ; i++)
	{
		currentNode->setElement
			(i, currentNode->getElement(i+1));
		currentNode->setBranch
		    (i, currentNode->getBranch(i+1));
	}
	currentNode->setNumbElements
			(currentNode->getNumbElements() - 1);
}

int main()
{
	AppClass * theApp = new AppClass();
	theApp->run();
	return 0;
} 

