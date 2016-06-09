#include<iostream>
#include<vector>

#define INITIAL_SIZE 25
#define SIZE_INCREMENT 10 

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
	    void   getKey(int &key)  { key = thing_id; }
	private:
		int thing_id;
		string thing_name;
}; 

template <class E ,class K>
class VectorMgr
{
	private:
		int total_elements,current_size;
		E * theVector;
	public:
		VectorMgr(int size) //pass in initial size
			:total_elements(0),current_size(size)
		{
			theVector = new E[size];
		}
		VectorMgr(VectorMgr *iVector)
			:current_size(iVector->getSize()),total_elements(iVector->getNumbElements())
		{
			theVector = new E[current_size];
			for(int i = 0 ; i < total_elements ; i++ )
				iVector->getElement(i,theVector[i]);
		}
		~VectorMgr() { delete [] theVector; }
		bool addElement(E);//pass in a single element
		bool addElement(E,int);//pass in element and index
		bool setElement(E,int);//pass in element and index
		//pass in ordinal position of element
		bool getElement(int , E &);
		//pass in ordinal position of element to delete
		bool deleteElement(int );
		//pass in key value ;return ordinal value
		bool findElement(K,int &pos);
		void resize(int );//pass in new size
		int  getNumbElements() {return total_elements;}//return total elements in vector
		void decrementNumbElements() { total_elements--;}
		int  getSize() {return current_size;}//return current size
		bool isEmpty() {return total_elements == 0;}//true if vector is empty
};

class PQueue
{
	private:
		VectorMgr<Thing,int> * theVector;//implement as a vector
		void buildHeap(int,int,VectorMgr<Thing,int> *);
	public:
		PQueue()
		{
			 theVector = new VectorMgr<Thing,int>(20);//here needs change 
		}
		PQueue(int );//pass in initial size
		~PQueue();
		void insert(Thing );
		bool remove(Thing &);
		void heapsort();//for demonstration purposes only 
		VectorMgr<Thing,int> *getVector() { return theVector; }//used by iterator
};

template<class A , class B>
class VectorItr
{
	private:
		VectorMgr<A,B> * theVector;
		int numb_elements;
		int current_index;
		
	public:
		//pass in array manager and total elements
		VectorItr(VectorMgr<A,B> *inVector ,int iElements)
			:theVector(inVector),current_index(0),numb_elements(iElements) 
		{ }
		bool getNext(A &nextObject)
		{
			bool result = false ;
			if(current_index < numb_elements)
			{
				theVector->getElement(current_index ,nextObject);
				result = true;
				current_index ++ ;
			}
			return result;
		}
};


class AppClass
{
	private:
		PQueue * thePQueue;
		int simpleMenu();
		void addThing();
		void deleteThing();
		void findThing();
		void listThings();
		void sortThing();
	public:
		AppClass()
		{
			thePQueue = new PQueue();
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
			case 4:
				listThings();
				break;
			case 5:
				sortThing();
				break;
			case 9:
				break;
			default:
				cout << "Unreconignized menu option ." << endl;
		}
	}
}

void AppClass::sortThing()
{
	thePQueue->heapsort();
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
	thePQueue->insert(*newThing);
}

void AppClass::findThing()
{
	int ID;
	cout << "ID to find:";
	cin>>ID;
	
	VectorItr<Thing , int> Itr(thePQueue->getVector() , thePQueue->getVector()->getNumbElements());
	bool result;
	Thing current;
	while(result = Itr.getNext(current))
	{
		if(current.getID() == ID)
		{
			cout << "Find the Thing!\n"
				 << "ID = " << current.getID() <<' ' 
				 << "Name = "<<current.getName()
				 <<endl; 
			return ;
		}		
	}
	cout<<"failed!"<<endl;
	return ;
}

void AppClass::listThings()
{
	VectorItr<Thing , int> Itr(thePQueue->getVector() , thePQueue->getVector()->getNumbElements());
	bool result;
	Thing current;
	while(result = Itr.getNext(current))
	{
		cout << "ID = " << current.getID() <<' ' 
		 << "Name = "<<current.getName() << endl;
	}
}

void AppClass::deleteThing()
{
	Thing current;
	bool result = thePQueue->remove(current);
	if(result==true)
	{
		cout << "succeed!\n";
	}
	else
	{
		cout << "failed!\n";
	}
}


int AppClass::simpleMenu()
{
	int choice;
	cout <<"\nYou can: "
		 <<"\n 1.Add an item"
		 <<"\n 2.Delete first item"
		 <<"\n 3.find elements"
		 <<"\n 4.list elements"
		 <<"\n 5.sort elements"
		 <<"\n 9.Quit"
		 <<"\n\n"
		 <<"Choice: ";
	cin>>choice;
	return choice;
}

template <class E ,class K>
bool VectorMgr<E,K>::addElement(E theElement)
{
	bool result = true ;
	if(total_elements == current_size)
		return false;//vector is full
	else
	{
		theVector[total_elements++] = theElement;
	}
}

template <class E ,class K>
bool VectorMgr<E,K>::addElement(E theElement , int index)
{
	bool result = true ;
	if(index <= current_size)
	{
		theVector[index] = theElement;
		total_elements++;
	}
	else
		result = false ;
	return result;
}

template <class E ,class K>
bool VectorMgr<E,K>::setElement(E theElement , int index)
{
	bool result = true ;
	if(index <= total_elements)
		theVector[index] = theElement;
	else
		result = false ;
	return result;
}

template <class E ,class K>
bool VectorMgr<E,K>::getElement(int index , E& theElement)
{
	bool result = true ;
	if(index >= total_elements)
		result = false ;
	else
		theElement = theVector[index];
	return result;
}

template <class E ,class K>
bool VectorMgr<E,K>::deleteElement(int element)
{
	bool result = true ;
	if(element >= total_elements )
		result = false ;
	else
	{
		for(int i = element ; i < total_elements - 1 ; i++)
			theVector[i] = theVector[i+1];
		total_elements--;
	}
	return result;
}

template <class E ,class K>
bool VectorMgr<E,K>::findElement(K searchValue , int & element)
{
	bool result = true;
	int i = 0;
	while(i < total_elements)
	{
		if(theVector[i].getKey() == searchValue)
			element = i;
		i++;
	} 
	if(i >= total_elements)
		result = false ;
	return result;
}

template <class E ,class K>
void VectorMgr<E,K>::resize(int newSize)
{
	char yes_no;
	if(newSize < total_elements)
	{
		cout << "\nNew size is too small to contain all exiting elements"
		     << "\nDo you want to truncate the vector（y/n）"
		     << endl;
		cin >> yes_no;
		if(yes_no == 'y')
			total_elements = newSize;
		else
			return ;
	}
	
	E * newVector = new E[newSize]; 
	if(!newVector)
	{
		cout << "\nCannot create vector.";
		return ;
	}
	for(int i = 0 ; i < total_elements ; i++)
		newVector[i] = theVector[i];
	delete [] theVector ;
	theVector = newVector;
	current_size = newSize;
}

void PQueue::insert(Thing newThing)
{
	int newKey;
	newThing.getKey(newKey);
	Thing theThing;
	
	int numbElements  = theVector->getNumbElements();
	
	//Add elements if vector is full
	if(numbElements + 1 >= theVector->getSize())
		theVector->resize(theVector->getSize() + SIZE_INCREMENT);
		
	int position = numbElements++;
	int storedKey;
	theVector->getElement( (position-1)/2 , theThing);
	theThing.getKey(storedKey);
	while(position > 0 && newKey >=storedKey)
	{
		theVector->setElement(theThing , position);
		position = (position - 1)/2;
		theVector->getElement( (position-1)/2 , theThing);
		theThing.getKey(storedKey);
	}
	
	theVector->addElement(newThing , position);
} 

bool PQueue::remove(Thing &removedThing)
{
	bool result = theVector->isEmpty();
	if(result)
		return false;
	
	theVector->getElement(0,removedThing);
	int lastIndex = theVector->getNumbElements() - 1;
	Thing lastElement;
	theVector->getElement(lastIndex , lastElement);
	theVector->setElement(lastElement , 0);
	theVector->decrementNumbElements();
	
	buildHeap( 0 , theVector->getNumbElements() , theVector);
	return true;
} 

void PQueue::buildHeap(int position , int size,
                     VectorMgr<Thing,int>* buildVector)
{
	int key = 0 ,key0 = 0, key1 = 0;
	
	Thing theThing , theThing1 , theThing0;
	buildVector->getElement(position , theThing);
	theThing.getKey(key);
	
	int childPosition;
	while(position < size)
	{
		childPosition = position * 2 + 1;
		if(childPosition < size)
		{
			buildVector->getElement(childPosition , theThing0);
			theThing0.getKey(key0);
			bool result = buildVector->getElement(childPosition + 1 ,theThing1);
			if(result)//I change here
				theThing1.getKey(key1);
			if( (childPosition + 1 < size) && key1 > key0 )
				childPosition += 1;
			if(key > key0 && key < key1)
			{
				buildVector->setElement(theThing , position);
				return ;
			}
			else
			{
				Thing childThing;
				buildVector->getElement(childPosition , childThing);
				buildVector->setElement(childThing , position);
				position = childPosition; 
			}
		}
		else
		{
			buildVector->setElement(theThing , position);
			return ;
		}
	}
}

void PQueue::heapsort()
{
	//若不是二叉堆 需要以下代码转化
	/*
	for(int i = numbELements/2 ; i >= 0 ; i--)
		buildHeap(i , numbElements ,theVector );
	*/
	//sorts a copy and display the sorted copy
	VectorMgr<Thing , int> * copyVector = 
		new VectorMgr<Thing , int>(theVector);
	
	int numbElements = copyVector->getNumbElements();
	
	for(int i = numbElements - 1 ; i > 0 ; i--)
	{
		Thing tempThing , iThing , firstThing ;
		copyVector->getElement(i ,iThing);
		copyVector->getElement(0 ,firstThing);
		tempThing = firstThing ;
		copyVector->setElement(iThing , 0);
		copyVector->setElement(tempThing , i );
		
		buildHeap( 0 , i , copyVector);
	}
	
	Thing theThing ;
	cout << endl ;
	for(int i = 0; i < numbElements ; i++)
	{
		copyVector->getElement(i ,theThing);
		cout << i << ": " 
			 << theThing.getID() << " "
			 << theThing.getName() << " "
			 << endl;
	}
}


int main()
{
	AppClass * theApp = new AppClass();
	theApp->run();
	return 0;
} 



