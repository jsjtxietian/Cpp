#include<iostream>
#include<cstring>

using namespace std; 

class Arrayable
{
	public:
		Arrayable() { }
		virtual int getKey() = 0;
};

class Thing : public Arrayable
{
	public:
		Thing() { }
		Thing(int ,char []);
		int getID() { return thing_id ;}
		char *getName()  { return thing_name ;}
		int getKey() { return thing_id ;}
		
	private:
		int thing_id;
		char thing_name[20];
}; 

Thing::
Thing(int iID , char iName[])
{
	thing_id = iID;
	strcpy(thing_name , iName);
}

#define MAX_ELEMENTS 10

class ArrayMgr
{
	private:
		int total_elements ;
		Thing * theArray[MAX_ELEMENTS];
	
	public:
		ArrayMgr() { total_elements = 0 ;}
		
		bool addElement (Thing *);
		bool getElement(int , Thing *&);//pass in position,return element value
		bool deleteElement( int ); //pass in position
		bool findElement(int ,int &);//pass in element value,return ordinal value
		int getSize() { return total_elements ; }
}; 

bool ArrayMgr::
addElement(Thing *newobject)
{
	bool result;
	if(total_elements < MAX_ELEMENTS )
	{
		theArray[total_elements++] = newobject;
		result = true ;
	}
	else
	{
		result = false;
	}
	return result;
}

bool ArrayMgr::
getElement(int pos , Thing * &element)
{
	bool result;
	
	if(pos > total_elements || total_elements == 0)
	{
		result = false ;
	}
	else
	{
		element = theArray[pos];
		result = true ;
	}
	return result ;
}

bool ArrayMgr::
deleteElement( int pos)
{
	bool result ;
	
	if(pos > total_elements || total_elements == 0)
	{
		result = false ;
	}
	else
	{
		for(int ix = pos; ix < total_elements - 1 ; ix++)
		{
			theArray[ix] = theArray[ix+1];
		}
		total_elements--;
		result = true;
	}
	return result;
}

bool ArrayMgr::
findElement( int searchValue ,int &pos)
{
	bool result = true ;
	int i = 0;
	pos = -1;
	
	while(i < total_elements)
	{
		if(theArray[i]->getKey() == searchValue)
		{
			pos = i;
		}
		i++;
	}
	if(pos == -1)
	{
		result = false ;
	}
	return result;
}


#define ADD          1
#define DELETE       2
#define RETRIEVE     3
#define FIND         4
#define LIST         5
#define SIZE         6
#define EXIT         9


class AppClass
{
	private:
		ArrayMgr *testArray;
		int  menu();
		void add();
		void remove();
		void retrieve();
		void find();
		void list();
		void size();
		
	public:
		AppClass() 
		{
			testArray = new ArrayMgr(); 
		}
		void run();
};

void AppClass::
run()
{
	int choice ;
	
	while( (choice = menu())!= EXIT )
	{
		switch(choice)
		{
			case ADD:
				add();
				break;
			case DELETE:
				remove();
				break;
			case RETRIEVE:
				retrieve();
				break;
			case FIND:
				find();
				break;
			case LIST:
				list();
				break;
			case SIZE:
				size();
				break;
		}
	}
}

int AppClass::
menu()
{
	int choice;
	cout <<"\nYou can: "
		 <<"\n 1.Add an item"
		 <<"\n 2.Delete an item"
		 <<"\n 3.Retrieve an item by its position in the structure"
		 <<"\n 4.Find ordinary position of element"
		 <<"\n 5.List all items"
		 <<"\n 6.Get size of structure"
		 <<"\n 9.Exit"
		 <<"\n\n"
		 <<"Choice: ";
	cin>>choice;
	return choice;
}

void AppClass::
add()
{
	int ID ;
	char name[20];
	cout<<"\nEnter a Thing ID: ";
	cin >> ID;
	cout<<"\nEnter a Thing name: ";
	cin >> name;
	
	Thing * newobject = new Thing(ID,name);
	bool result = testArray->addElement(newobject);
	
	if(result)
	{
		cout << "\nElements added successfully." << endl;
	}
	else
	{
		cout << "Couldn't add an element because the Array is full" <<endl;
	}
}

void AppClass::
remove()
{
	int pos ;
	cout<<"\nEnter the position to delete: ";
	cin >> pos;
	bool result = testArray->deleteElement(pos);
	
	if(result)
	{
		cout << "\nThe deletion is successful." << endl;
	}
	else
	{
		cout << "The deletion failed for the position was out of range" <<endl;
	}
}

void AppClass::
retrieve()
{
	int pos;
	cout<<"\nEnter an array position: ";
	cin >> pos;
	
	Thing * theThing ;
	bool result = 
		testArray->getElement(pos,theThing);
	
	if(result)
	{
		cout << "\nThe Thing at " << pos 
		     << " has an ID of " << theThing->getID()
			 << " and a name of " << theThing->getName() << "." << endl;
	}
	else
	{
		cout << "The position is out of Range." <<endl;
	}
}

void AppClass::
size()
{
	cout << "There are " << testArray->getSize()
	     << " elements in the array." <<endl;
}

void AppClass::
find()
{
	int ID,pos ;
	cout<<"\nEnter a value to find : ";
	cin >> ID;
	bool result = testArray->findElement(ID,pos);
	
	if(result)
	{
		cout << "\nThe thing with an ID of " <<ID
		     << " is in position " <<pos <<"." << endl;
	}
	else
	{
		cout << "\nThere is no Thing with an Id of "<< ID
		     << " in the array." <<endl;
	}
}


class ArrayItr
{
	private:
		ArrayMgr * theArray;
		int numb_elements;
		int current_index; 
		
	public:	
		ArrayItr(ArrayMgr *inArray ,int iElements)
			: theArray(inArray) , numb_elements(iElements)
		{
			current_index = 0;
		}
		bool getNext(Thing * &);
}; 

bool ArrayItr::getNext(Thing * &nextObject)
{
	bool result = false ;
	if(current_index < numb_elements)
	{
		theArray->getElement(current_index,nextObject);
		result = true;
		current_index ++ ;
	}
	return result;
} 

void AppClass::
list()
{
	Thing *theThing;
	ArrayItr *theItr = new ArrayItr(testArray,testArray->getSize() );
	int i = 0;
	bool result = theItr->getNext(theThing);
	while(result)
	{
		cout << i+1 << ":ID = " << theThing->getID() 
			 <<" Name = " << theThing->getName() << "." <<endl;
		result = theItr->getNext(theThing);
		i++;
	}
}



int main()
{
	AppClass * theApp = new AppClass();
	theApp->run();
	return 0;
}
