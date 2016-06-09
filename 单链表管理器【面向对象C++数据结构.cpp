#include<iostream>
#include<string>

using namespace std; 

class Listable
{
	public:
		Listable() { }
		virtual int getKey() = 0;
};

class Thing : public Listable
{
	public:
		Thing() { }
		Thing(int iID,string iName)
			:thing_id(iID) , thing_name(iName)
		{ }
		
		int    getID() const  { return thing_id ;}
		string getName()   const { return thing_name ;}
	    int    getKey()  { return thing_id ;}
		
	private:
		int thing_id;
		string thing_name;
}; 

class Node
{
	private:
		Thing *theThing;
		Node * next;
		
	public:
		Node(Thing *theObject)
			:theThing(theObject) ,next(0)
		{ }
		Node * getNext() { return next ;}
		Thing * getThing() { return theThing ;}
		void setNext(Node *nextNode)
		{ 
			next = nextNode ;
		}
};

class ListMgr
{
	private:
		Node *first;
		
	public:
		ListMgr()
			:first(0)
		{ }
		void insert(Thing *);
		Thing *find(int ); //locate by ID
		bool remove(int );
		Node *getfirst() {return first;} 
}; 

void ListMgr::
insert(Thing *theThing)
{
	Node *newNode ,*current,*previous;
	Thing *currentThing;
	
	newNode = new Node(theThing);
	int newKey = theThing->getKey();
	if(!newNode)
	{
		cout << "\nCannot create node." << endl;
		return ;
	}
	
	if(first == 0)
	{
		first = newNode ;
	}
	else
	{
		bool firstNode = true;
		current = first ;
		while(current != 0)
		{
			currentThing = current->getThing();//∞¥’’key≈≈–Ú 
			if(newKey < currentThing->getKey())
			{
				break;
			}
			previous = current ;
			current = current->getNext();
			firstNode = false ;
		}
		
		if(!firstNode)
		{
			previous->setNext(newNode);
		}
		else
		{
			first = newNode ;
		}
		newNode->setNext(current);
	}
}

bool ListMgr::
remove(int searchNumb)
{
	Thing *currentThing;
	Node * current ,* previous ,*next ;
	
	if(first == 0)
	{
		return false ;
	}
	
	bool firstNode = true ;
	current = first ;
	
	while(current != 0)
	{
		currentThing = current->getThing();
		if(searchNumb == currentThing->getKey())
		{
			break;
		}
		previous = current ;
		current = current->getNext();
		firstNode = false ;
	}
	
	if(current == 0)
	{
		return false ;
	}
	
	if(!firstNode)
	{
		next = current->getNext();
		previous->setNext(next);
	}
	else
	{
		first = current->getNext();
	}
	
	delete current->getThing();
	delete current;
	
	return true;
} 

Thing * ListMgr::
find(int searchNumb)
{
	Thing *currentThing;
	Node * current = first;
	
	while(current != 0)
	{
		currentThing = current->getThing();
		if(searchNumb == currentThing->getKey())
		{
			return currentThing;
		}
		current = current->getNext();
	}
	return 0;
}

#define INSERT       1
#define REMOVE_THING 2
#define VIEW         3
#define QUIT         9

class AppClass
{
	private:
		ListMgr * theList;
		int  menu();
		void addThing();
		void removeThing();
		void view();
	public:
		AppClass() { theList = new ListMgr();}
		void run(); 
};

void AppClass::
run()
{
	int choice ;
	
	while( (choice = menu()) != QUIT)
	{
		switch(choice)
		{
			case INSERT:
				addThing();
				break;
			case REMOVE_THING:
				removeThing();
				break;
			case VIEW:
				view();
				break;
			case QUIT:
				break;
			default:
				cout << "Unreconignized menu option ." << endl;
		}
	}
} 

int AppClass::
menu()
{
	int choice;
	cout <<"\nYou can: "
		 <<"\n 1.Add an item"
		 <<"\n 2.Remove an item"
		 <<"\n 3.View elements"
		 <<"\n 9.Quit"
		 <<"\n\n"
		 <<"Choice: ";
	cin>>choice;
	return choice;
}

void AppClass::
addThing()
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
	theList->insert(newThing);
}


void AppClass::
removeThing()
{
	int ID;
	cout << "ID to remove:";
	cin>>ID;
	bool result = theList->remove(ID);
	if(result)
	{
		cout << "succeed!\n";
	}
	else
	{
		cout << "failed!\n";
	}
}

class ListItr
{
	private:
		Node *current;
		ListMgr *theList;
	public:
		ListItr(ListMgr *whichList)
			:current(0),theList(whichList)
		{ }
		Thing * getNext();
};

Thing * ListItr::
getNext()
{
	if(current == 0)
	{
		current = theList->getfirst();
	}
	else
	{
		current = current->getNext();
	}
	
	if(current != 0)
	{
		return current->getThing();
	}
	else
	{
		return 0;
	}
}



void AppClass::
view()
{
	Thing *current ;
	ListItr * theIterator = new ListItr(theList);
	current = theIterator->getNext();
	cout << endl;
	while(current != 0)
	{
		cout << "ID = " << current->getID() 
		     << "; Name = " << current->getName()
		     << "." << endl;
		current = theIterator->getNext(); 
	}
}
int main()
{
	AppClass * theApp = new AppClass();
	theApp->run();
	return 0;
}




