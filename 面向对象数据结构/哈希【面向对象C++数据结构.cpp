#include<iostream>
#include<string>

#define TABLE_SIZE 203

using namespace std;

class Thing
{
	public:
		Thing() { }
		Thing(int iID,string iName)
			:thing_id(iID) , thing_name(iName)
		{ }
		
		int    getID() const  { return thing_id ;}
		string getName()   const { return thing_name ;}
	    void   getKey(string &key)  { key = thing_name ;}
		
	private:
		int thing_id;
		string thing_name;
}; 

class Hashtable
{
	private:
		Thing * table[TABLE_SIZE];
		int computeIndex(string key)
		{
			long sum = 0;
			for(int i = 0 ; i < key.size() ; i++)
				sum += key[i];
			return sum % TABLE_SIZE;
		}
		
	public:
		Hashtable()
		{
			for(int i = 0 ; i < TABLE_SIZE ; i++)
				table[i] = 0;
		}
		bool insert(Thing *);
		Thing * find(string);
		Thing * getThing(int index) { return table[index];}
		
};

class HashtableItr
{
	private:
		Hashtable * theTable;
		int index;
	public:
		HashtableItr(Hashtable *whichTable)
			:theTable(whichTable),index(-1)
		{	}
		bool getNext(Thing * & ,int &);	
};

bool HashtableItr::getNext(Thing *& theThing ,int & position)
{
	bool done = false ;
	//find next used position in table
	while(theTable->getThing(++index) == 0 && index < TABLE_SIZE);
	
	if( index == TABLE_SIZE)
	{
		done = true ;
		theThing = 0;
		position = -1;
	}
	else
	{
		theThing = theTable->getThing(index);
		position = index;
	}
	return done;
}

bool Hashtable::insert(Thing * newThing)
{
	string key ;
	newThing->getKey(key);
	int index = computeIndex(key);
	int computedindex = index;
	bool result = true ;
	
	if(table[index] == 0)
		table[index] = newThing;
	else
	{
		while(table[++index] !=0 && index < TABLE_SIZE); //find next open spot
		if(index == TABLE_SIZE)
		{
			int index = -1;
			//start again at top
			while(table[++index] !=0 && index < computedindex - 1);
			if(index == computedindex)
				result = false ;
			else
				table[index] = newThing;
		}
		else
			table[index] = newThing ;
	}
	return result;
}

Thing * Hashtable::find(string key)
{
	int index = computeIndex(key);
	int computedIndex = index;
	Thing * theThing = 0;
	string theKey;
	table[index]->getKey(theKey);
	
	if(theKey != key)
	{
		while(theKey != key && table[index] != 0 && index < TABLE_SIZE)
			table[++index]->getKey(theKey);
		if(theKey == key)
			theThing = table[index];
		if(index == TABLE_SIZE)
		{
			index = -1 ;
			while(theKey != key && table[++index] != 0 && index < computedIndex)
				table[index]->getKey(key);
			if(theKey == key)
				theThing = table[index];
		}
	}
	else
		theThing = table[index];
	return theThing;
}

class AppClass
{
	private:
		Hashtable* theTable;
		int  menu();
		void addThing();
		void view();
		void find();
	public:
		AppClass() { theTable = new Hashtable();}
		void run(); 
};

int AppClass::
menu()
{
	int choice;
	cout <<"\nYou can: "
		 <<"\n 1.Add an item"
		 <<"\n 2.Find an item"
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
	theTable->insert(newThing);
}

void AppClass::
run()
{
	int choice ;
	
	while( (choice = menu()) != 9)
	{
		switch(choice)
		{
			case 1:
				addThing();
				break;
			case 2:
				find();
				break;
			case 3:
				view();
				break;
			case 9:
				break;
			default:
				cout << "Unreconignized menu option ." << endl;
		}
	}
} 

void AppClass::view()
{
	HashtableItr *Itr = new HashtableItr(theTable);
	Thing * theThing ;
	int position;
	
	while( !Itr->getNext(theThing , position))
	{
		cout << "ID= " << theThing->getID()
			 << " Name = " << theThing->getName()
			 << endl;
	}
}

void AppClass::find()
{
	string name ;
	cout << "\nstring to find:";
	cin >> name;
	Thing * current = theTable->find(name);
	if(current)
	{
		cout <<"Found it!"
			 << "ID = " << current->getID() 
		     << "; Name = " << current->getName()
		     << "." << endl;
	}
	else
		cout << "Failed!" << endl;
}

int main()
{
	AppClass * theApp = new AppClass();
	theApp->run();
	return 0;
} 
