#include"SignUpSystem.h"

void ListMgr::
create(Thing *theThing)
{
	Node *newNode ,*current,*previous;

	newNode = new Node(theThing);
	if(!newNode)
	{
		cout << "\nCannot create node." << endl;
		return ;
	}
	
	if(first == nullptr)
	{
		first = newNode ;
	}
	else
	{
		current = first;
		while (current != 0)
		{
			previous = current;
			current = current->getNext();
		}
		previous->setNext(newNode);
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
		if(searchNumb == currentThing->getID())
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

void ListMgr::insert(Thing *theThing, int i)
{
	Node *newNode, *current, *previous;

	newNode = new Node(theThing);
	if (!newNode)
	{
		cout << "\nCannot create node." << endl;
		return;
	}

	if (i == 1)
	{
		newNode->setNext(first);
		first = newNode;
		return;
	}

	current = first;
	previous = first;
	while (i != 1)
	{
		previous = current;
		current = current->getNext();
		i--;
	}

	previous->setNext(newNode);
	newNode->setNext(current);
	
}

Thing * ListMgr::
find(int searchNumb)
{
	Thing *currentThing;
	Node * current = first;
	
	while(current != 0)
	{
		currentThing = current->getThing();
		if(searchNumb == currentThing->getID())
		{
			return currentThing;
		}
		current = current->getNext();
	}
	return 0;
}

void ListMgr::repair(Thing* newThing,int ID)
{
	Thing* currentThing;
	Node* newNode = new Node(newThing);
	Node* current = first;
	Node* prevoius = current;

	if (first->getThing()->getID() == ID)
	{
		Node* temp = first;
		newNode->setNext(first->getNext());
		first = newNode;
		delete temp->getThing();
		delete temp;
		return;
	}

	while (current!=nullptr)
	{
		currentThing = current->getThing();
		if (ID == currentThing->getID())
		{
			prevoius->setNext(newNode);
			newNode->setNext(current->getNext());
			delete current->getThing();
			delete current;
			break;
		}
		prevoius = current;
		current = current->getNext();
	}
}


void AppClass::
run()
{
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	cout << "�����뿼��������";
	int n;
	cin >> n;
	cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
	createThing(n);

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
			case SEARCH:
				searchThing();
				break;
			case REPAIR:
				repairThing();
				break;
			case VIEW:
				view();
				break;
			case QUIT:
				exit(1);
				break;
			default:
				cout << "δ�϶��ķ���" << endl;
		}
	}
} 

int AppClass::
menu()
{
	int choice;
	cout << "\n��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
	cin>>choice;
	return choice;
}

void AppClass::
addThing()
{
	Thing * newThing;

	cout << "��������Ҫ����ѧ����λ�ã�";
	int i;
	cin >> i;

	cout << "����������Ҫ�����ѧ���Ŀ��ţ��������Ա����估�������" << endl;
	int number;
	string name;
	string sex;
	int age;
	string category;
	cin >> number >> name >> sex >> age >> category;

	newThing = new Thing(number,name,sex,age,category);
	theList->insert(newThing,i);
}

void AppClass::
removeThing()
{
	int ID;
	cout << "��������Ҫɾ��ѧ���Ŀ��ţ�" << endl;
	cin>>ID;
	bool result = theList->remove(ID);

	if(result)
	{
		cout << "�ɹ�!\n";
	}
	else
	{
		cout << "ʧ��!\n";
	}
}

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
show(Thing *current)
{
	cout << endl;
	cout << left << setw(10) << "����";
	cout << left << setw(10) << "����";
	cout << left << setw(10) << "�Ա�";
	cout << left << setw(10) << "����";
	cout << left << setw(10) << "�������" << endl;

	cout << left << setw(10) << current->getID();
	cout << left << setw(10) << current->getName();
	cout << left << setw(10) << current->getSex();
	cout << left << setw(10) << current->getAge();
	cout << left << setw(10) << current->getCategory() 
		 << '\n' << endl;
}

void AppClass::
view()
{
	Thing *current ;
	ListItr * theIterator = new ListItr(theList);
	current = theIterator->getNext();

	cout << endl;
	cout << left << setw(10) << "����";
	cout << left << setw(10) << "����";
	cout << left << setw(10) << "�Ա�";
	cout << left << setw(10) << "����";
	cout << left << setw(10) << "�������" << endl;

	while(current != 0)
	{
		cout << left << setw(10) << current->getID();
		cout << left << setw(10) << current->getName();
		cout << left << setw(10) << current->getSex();
		cout << left << setw(10) << current->getAge();
		cout << left << setw(10) << current->getCategory() 
			 << endl;
		
		current = theIterator->getNext(); 
	}
}

void AppClass::repairThing()
{
	cout << "��������Ҫ�޸ĵ�ѧ���Ŀ��ţ�" << endl;
	int ID;
	cin >> ID;
	cout << "����������Ҫ�޸ĵ�ѧ���Ŀ��ţ��������Ա����估�������" << endl;
	int number;
	string name;
	string sex;
	int age;
	string category;
	cin >> number >> name >> sex >> age >> category;
	Thing * currentThing = new Thing(number, name, sex, age, category);
	theList->repair(currentThing,ID);
}

void AppClass::createThing(int n)
{
	for (int i = 1; i <= n; i++)
	{
		int number;
		string name;
		string sex;
		int age;
		string category;
		cin >> number >> name >> sex >> age >> category;
		Thing* newThing = new Thing(number, name, sex, age, category);
		theList->create(newThing);
	}

}

void AppClass::searchThing()
{
	cout << "��������Ҫ����ѧ���Ŀ��ţ�" << endl;
	int ID;
	cin >> ID;
	Thing * currentThing = theList->find(ID);
	if (currentThing != nullptr)
	{
		show(currentThing);
	}
	else
	{
		cout << "Ѱ�Ҳ���=��=\n" << endl;
	}
}

int main()
{
	AppClass * theApp = new AppClass();
	theApp->run();
	return 0;
}




