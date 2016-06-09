#include<iostream>
#include<string>
#include<cmath>

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
		Thing(int iID , string iName)
		{
			thing_id = iID;
			thing_name  = iName; 
		}

		int getID() { return thing_id ;}
		string getName()  { return thing_name ;}
		int getKey() { return thing_id ;}
		
	private:
		int thing_id;
		string thing_name;
}; 


#define MAX_ELEMENTS 10
#define STACK_SIZE 10

class ArrayMgr
{
	private:
		int total_elements ;
		Thing * theArray[MAX_ELEMENTS];
		void quicksort(Thing * [] , int , int );
		void partition(Thing *[] , int ,int , int &);
		void mergesort(Thing *[], const int & , const int &);
		void domerge(Thing *[] , const int & ,const int & ,const int &);
		void radixsort(int , Thing *[] , Thing *[]);
		
	public:
		ArrayMgr() { total_elements = 0 ;}
		
		bool addElement (Thing *);
		bool getElement(int , Thing *&);//pass in position,return element value
		bool deleteElement( int ); //pass in position
		bool findElement(int ,int &);//pass in element value,return ordinal value
		int  getSize() { return total_elements ; }
		Thing *search(int );//二分查找 
		
		void bubble();
		void selection(); 
		void insertion1();//新数组的插入排序 
		void insertion2();//对现有数组进行插入排序 
		void shell();
		void quick1();//递归 
		void quick2();//堆栈 
		void merge();
		void radix();//正整数 
}; 

Thing *ArrayMgr::search(int ID)
{
	int top , bottom ,middle ;
	top = 0;
	bottom = total_elements - 1 ;
	
	bool found = false ;
	Thing * result = 0;
	
	while(top <= bottom && !found)
	{
		middle = (top + bottom) / 2 ;//find a new middle element
		if(theArray[middle]->getID() == ID)
		{
			result = theArray[middle];
			found = true ;
		}
		else if(theArray[middle]->getID() < ID)
			top = middle + 1;
		else
			bottom = middle - 1;
	} 
	return result ;
}

void ArrayMgr::radixsort(int theDigit, Thing *destArray[] , Thing *sortArray[])
{
	//Note that this function must also have access to the total
	//number of items being sorted and the array containing the
	//original items.
	int frequency[10];
	//intialize frequency counting array
	for(int i = 0 ; i < 10 ; i++)
		frequency[i] = 0;
	
	int digit;
	float value;
	//count occurences of each value
	for(int i = 0 ; i < total_elements ; i++)
	{
		value = ((float) sortArray[i]->getKey() / (pow(10,theDigit)));
		digit = (int) ((float)sortArray[i]->getKey() / (pow(10,theDigit)));
		digit = (int) ((value - (float)digit ) * 10);
		frequency[digit]++;
	}
	
	int index[MAX_ELEMENTS];
	index[0] = 0;
	for(int i = 1 ; i < MAX_ELEMENTS ; i++)
		index[i] = index[i-1] + frequency[i-1];
	
	for(int i = 0 ; i < total_elements ; i++)
	{
		value = ((float)sortArray[i]->getKey() / (pow(10,theDigit)));
		digit = (int) ((float)sortArray[i]->getKey() / (pow(10,theDigit)));
		digit = (int)((value - (float)digit ) * 10);
		destArray[index[digit]++] = sortArray[i];
	}
}

void ArrayMgr::radix()
{
	Thing * sortArray[MAX_ELEMENTS];
	Thing * destArray[MAX_ELEMENTS];
	for(int i = 0 ; i < total_elements ; i++)
		sortArray[i] = theArray[i];
	
	int maxKey = sortArray[0]->getKey();//first find largest key
	for(int i = 1 ; i < total_elements ; i++)
	{
		if(sortArray[i]->getKey() > maxKey)
		{
			maxKey = sortArray[i]->getKey();
		}
	}
	
	int passcount = 1;
	int numb_digits = log10(maxKey) + 1;
	
	//This loop contains what at first looks to be redundant code
	//However , it actually copies data between two arrays
	for(int i = 0 ; i <= numb_digits  ; i += 2)
	{
		radixsort(i , destArray , sortArray);
		cout << "\nPass # " << i + 1;
		for(int k = 0 ; k < total_elements ; k++)
			cout << "\n ID: " << destArray[k]->getID()
				 << " Name: " << destArray[k]->getName();
		radixsort(i+1 , sortArray , destArray);
		cout << "\nPass # " << i + 2;
		for(int k = 0 ; k < total_elements ; k++)
			cout << "\n ID: " << sortArray[k]->getID()
				 << " Name: " << sortArray[k]->getName();
	}
}

void ArrayMgr::merge()
{
	Thing * sortArray[MAX_ELEMENTS];
	for(int i = 0 ; i < total_elements ; i++)
		sortArray[i] = theArray[i];
	//initial the sort
	mergesort(sortArray , 0 , total_elements - 1); 
}

void ArrayMgr::mergesort(Thing *theArray[], const int & low, const int &high)
{
	//show array at the beginning of each recursive call
	static int passcount = 1 ;
	cout << "\nCall # " << passcount++;
		for(int k = 0 ; k < total_elements ; k++)
			cout << "\n ID: " << theArray[k]->getID()
				 << " Name: " << theArray[k]->getName();
	
	if(low < high)
	{
		int mid = (low + high) / 2;//find the middle element
		
		mergesort(theArray , low , mid);
		mergesort(theArray , mid + 1 , high);
		//demerge the halves back together
		domerge(theArray , low, mid , high);
		cout << "\nAfter merge ";
		for(int k = 0 ; k < total_elements ; k++)
			cout << "\n ID: " << theArray[k]->getID()
				 << " Name: " << theArray[k]->getName();
	}
}

void ArrayMgr::domerge(Thing *theArray[] , const int & low , const int & mid ,const int &high)
{
	int topPtr = low ;//pointer to top half of array
	int midPtr = mid + 1 ;//pointer to middle ;start of bottom half
	int resultPtr = 0;//pointer to merged away
	Thing * tempArray[MAX_ELEMENTS];
	
	//copy into temporary array from two sorted halves in correct order
	while(topPtr <= mid && midPtr <= high)
	{
		if(theArray[topPtr]->getKey() < 
			theArray[midPtr]->getKey())
		{
			tempArray[resultPtr] = theArray[topPtr];
			topPtr++; 
		}
		else
		{
			tempArray[resultPtr] = theArray[midPtr];
			midPtr++;
		}
		resultPtr++;
	}
	//copy remaining elements
	//at most one of these two loops will excute
	while(topPtr <= mid)
	{
		tempArray[resultPtr] = theArray[topPtr];
		topPtr++;
		resultPtr++;
	}
	while(midPtr <= high)
	{
		tempArray[resultPtr] = theArray[midPtr];
		midPtr++;
		resultPtr++;
	}
	//now copy back to original way
	topPtr = low ;
	resultPtr = 0;
	
	while(topPtr <= high)
	{
		theArray[topPtr] = tempArray[resultPtr];
		topPtr++;
		resultPtr++;
	}
}

void ArrayMgr::quick2()
{
	Thing * sortArray[MAX_ELEMENTS];
	for(int i = 0 ; i < total_elements ; i++)
		sortArray[i] = theArray[i];
	
	int low = 0;
	int high = total_elements - 1;
	
	int pivotPoint ;
	int stackPtr = -1 ;
	int lowStack[STACK_SIZE] , highStack[STACK_SIZE];
	int passcount = 1;
	
	do
	{
		if(stackPtr > -1)
		{
			low  =  lowStack[stackPtr];
			high = highStack[stackPtr];
			stackPtr--;
		}
		
		while(low < high)
		{
			partition(sortArray , low , high , pivotPoint);
			if(pivotPoint - low < high - pivotPoint)
			{
				if(stackPtr >= STACK_SIZE)
				{
					cout << "\nStack overflow.Cannot complete sort.";
					return ;
				}
				stackPtr++;
				lowStack[stackPtr] = pivotPoint + 1;
				highStack[stackPtr] = high ;
				high = pivotPoint - 1;
			}
			else
			{
				if(stackPtr >= STACK_SIZE)
				{
					cout << "\nStack overflow.Cannot complete sort.";
					return ;
				}
				stackPtr++;
				lowStack[stackPtr] = low ;
				highStack[stackPtr] = pivotPoint - 1;
				low = pivotPoint - 1 ;
			}
			cout << "\nPass # " << passcount++;
			for(int k = 0 ; k < total_elements ; k++)
				cout << "\n ID: " << sortArray[k]->getID()
					 << " Name: " << sortArray[k]->getName();
		}
	}while(stackPtr > -1);
}

void ArrayMgr::quick1()
{
	Thing * sortArray[MAX_ELEMENTS];
	for(int i = 0 ; i < total_elements ; i++)
		sortArray[i] = theArray[i];
	
	//initial the sort
	quicksort(sortArray , 0 , total_elements - 1); 
}

void ArrayMgr::quicksort(Thing *theArray[] , int low , int high)
{
	int pivotPoint ; 
	//show array at begining of each recursive call
	static int passcount = 1 ;
	cout << "\nCall # " << passcount++;
	for(int k = 0 ; k < total_elements ; k++)
		cout << "\n ID: " << theArray[k]->getID()
			 << " Name: " << theArray[k]->getName();
	cout << endl;
	if(low < high)
	{
		//partition the array
		partition(theArray , low , high , pivotPoint);
		cout << "\nPivot point: " << pivotPoint << endl;
		//sort the top half
		quicksort(theArray , low , pivotPoint - 1 );
		//sort the bottom half
		quicksort(theArray , pivotPoint + 1 , high );
	}
}

void ArrayMgr::partition(Thing *theArray[] , int low , int high , int & pivotPoint)
{
	Thing * tempThing ;
	pivotPoint = low ;
	int pivotKey = theArray[pivotPoint]->getKey();
	
	while(low <= high)
	{
		if(theArray[low]->getKey() <= pivotKey)
			low++;
		else if(theArray[high]->getKey() >= pivotKey)
			high--;
		else
		{
			tempThing = theArray[high];//swap
			theArray[high] = theArray[low];
			theArray[low] = tempThing ;
			low++;
			high--;
		}
	}
	tempThing = theArray[high];
	theArray[high] = theArray[pivotPoint];
	theArray[pivotPoint] = tempThing ;
	//this is the spot between the two partitions
	pivotPoint = high ;
}

void ArrayMgr::shell()
{
	Thing * sortArray[MAX_ELEMENTS] , *tempThing;
	for( int i = 0 ; i < total_elements ; i++) //sort a copy
		sortArray[i] = theArray[i];
	
	int passcount = 1 ; //used for display only
	int increment = total_elements / 2 ;
	int sortIndex ;
	
	while(increment >= 1)
	{
		for(int i = increment ; i < total_elements ; i++)
		{
			tempThing = sortArray[i];
			for(sortIndex = i - increment ; 
			    sortIndex >= 0 && tempThing->getKey() < sortArray[sortIndex]->getKey();
				sortIndex -= increment)
					sortArray[sortIndex + increment] = sortArray[sortIndex];
			sortArray[sortIndex + increment] = tempThing ;
		}
		//show array after one pass 
		cout << "Increment: " << increment
	 		 << "\nPass # " << passcount++ ;
		for(int k = 0 ; k < total_elements ; k++)
			cout << "\n ID: " << sortArray[k]->getID()
				 << " Name: " << sortArray[k]->getName();
		cout << endl;
		//compute new increment
		if(increment == 2)//last must be 1
			increment = 1 ;
		else
			increment = increment / 2.2 ;
	}
}

void ArrayMgr::insertion2()
{
	Thing * sortArray[MAX_ELEMENTS] , *tempThing;
	for( int i = 0 ; i < total_elements ; i++) //sort a copy
		sortArray[i] = theArray[i];
	
	for(int i = 1 ; i < total_elements ; i++)
	{
		//if out of order 
		if(sortArray[i]->getKey() < sortArray[i-1]->getKey())
		{
			tempThing = sortArray[i];//save elelemt to be moved
			//index into sorted portion of array
			int sortedIndex = i ;
			bool found = false ;
			while(!found) //look for place to insert element
			{
				//move an element up
				sortArray[sortedIndex] = sortArray[sortedIndex - 1];
				sortedIndex--;
				if(sortedIndex == 0)
					found = true ;
				else
					found = sortArray[sortedIndex - 1]->getKey()
						<= tempThing->getKey();
			}
			sortArray[sortedIndex] = tempThing ;
		}
		//show array after pass has been made 
		cout << "\nInsertion # " << i ;
		for(int k = 0 ; k < total_elements ; k++)
			cout << "\n ID: " << sortArray[k]->getID()
				 << " Name: " << sortArray[k]->getName();
		cout << endl;
	}
}

void ArrayMgr::insertion1()
{
	Thing * sortArray[MAX_ELEMENTS] ;//target of sort
	sortArray[0] = theArray[0];
	int sortCount = 0;//last element used in sort array
	//loop through original array
	for(int i = 1 ; i < total_elements ; i++)
	{
		int insert_spot = -1 ;
		for(int j = sortCount ; j >= 0 ; j--)
		{
			//find insert spot
			if(theArray[i]->getKey() > sortArray[j]->getKey())
				insert_spot = j + 1;
			if(insert_spot > -1)
				break ;
		}
		if(insert_spot == -1)
			insert_spot = 0;
		
		for(int k = sortCount ; k >= insert_spot ; k--)
			sortArray[k+1] = sortArray[k];//move down
		sortArray[insert_spot] = theArray[i];//insert
		sortCount++ ;//used to limit display to valid elements
		
		//show array after insertion has been made
		cout << "\nInsertion #" << i ;
		for(int k = 0 ; k <= sortCount ; k++)
			cout << "\n ID: " << sortArray[k]->getID()
				 << " Name: " << sortArray[k]->getName();
		cout<< endl ;
	}
}

void ArrayMgr::selection()
{
	Thing * sortArray[MAX_ELEMENTS] , *tempThing;
	int maxIndex , maxKey ;//index of maximum element
	for( int i = 0 ; i < total_elements ; i++) //sort a copy
		sortArray[i] = theArray[i];
		
	int passcount = 1;
	//if all elements are in place except the last one,
	//then last one must be too.
	//therefore can stop loop at 1 rather than 0
	for(int i = total_elements - 1 ; i >= 1 ; i-- )
	{
		//find elelment with max key value
		//that isn't in the right place yet
		maxKey = sortArray[0]->getKey();
		maxIndex = 0;
		for(int j = 1 ; j <= i ; j++)
		{
			if(sortArray[j]->getKey() > maxKey)
			{
				maxKey = sortArray[j]->getKey();
				maxIndex = j ;
			}
		}
		//move it to the bottom ; i represents bottom of array
		tempThing = sortArray[maxIndex];
		sortArray[maxIndex] = sortArray[i];
		sortArray[i] = tempThing ;
		
		//show array after swap has been made 
		cout << "\nPass # " << passcount++ ;
		for(int k = 0 ; k < total_elements ; k++)
			cout << "\n ID: " << sortArray[k]->getID()
				 << " Name: " << sortArray[k]->getName();
		cout << endl ;
	}
}

void ArrayMgr::bubble()
{
	Thing * sortArray[MAX_ELEMENTS] , *tempThing;
	for( int i = 0 ; i < total_elements ; i++) //sort a copy
		sortArray[i] = theArray[i];
	
	bool swap_made = true ;
	int count = 0;//cout number of passes through away
	int unsortedIndex = total_elements - 1;
	int tmpIndex = 0; 
	while(swap_made)
	{
		swap_made = false ; 
		count ++ ;
		for(int i = 0 ; i < unsortedIndex ; i++)//one pass
		{
			//swap
			if(sortArray[i]->getKey() > sortArray[i+1]->getKey())
			{
				swap_made = true ;
				tempThing = sortArray[i];
				sortArray[i] = sortArray[i+1];
				sortArray[i+1] = tempThing;
				tmpIndex = i;
			}
		}
		unsortedIndex = tmpIndex;
		//show array after pass has been made 
		cout << "\nPass # " << count ;
		for(int i = 0 ; i < total_elements ; i++)
			cout << "\n ID: " << sortArray[i]->getID()
				 << " Name: " << sortArray[i]->getName();
		cout<< endl ;
	}
}



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
#define SORT         7
#define RESET        8
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
		void sort();
		void reset();
		
	public:
		AppClass() 
		{
			testArray = new ArrayMgr(); 
		}
		void run();
};

void AppClass::sort()
{
	cout<< "\nChoose a sort method:"
		<< "\n 1.Bubble"
		<< "\n 2.Selection"
		<< "\n 3.Insertion1" 
		<< "\n 4.Insertion2"
		<< "\n 5.Shell"
		<< "\n 6.Quick1"
		<< "\n 7.Quick2"
		<< "\n 8.Merge"
		<< "\n 9.Radix"
		
		<< "\n 99.EXIT"
		<< endl;
	int choice ;
	cin >> choice ;
	switch(choice)
	{
		case 1:
			testArray->bubble();
			break;
		case 2:
			testArray->selection();
			break;
		case 3:
			testArray->insertion1();
			break; 
		case 4:
			testArray->insertion2();
			break;
		case 5:
			testArray->shell();
			break;
		case 6:
			testArray->quick1();
			break;
		case 7:
			testArray->quick2();
			break;
		case 8:
			testArray->merge();
			break;
		case 9:
			testArray->radix();
			break;
	}
}

void AppClass::reset()
{
	testArray = new ArrayMgr(); 
}

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
			case SORT:
				sort();
				break;
			case RESET:
				reset();
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
		 <<"\n 7.Examine sort methods"
		 <<"\n 8.Reset the array" 
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
	string name;
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
