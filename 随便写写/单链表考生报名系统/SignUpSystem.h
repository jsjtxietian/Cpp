#pragma once
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

#define INSERT       1
#define REMOVE_THING 2
#define SEARCH       3
#define REPAIR       4
#define VIEW         5

#define QUIT         0

class Thing 
{
public:
	Thing() { }
	Thing(int iID, string iName, string sex , int iAge,string iType)
		:thing_id(iID), thing_name(iName),_sex(sex),_age(iAge),_category(iType)
	{ }

	int    getID() const { return thing_id; }
	string getName() const { return thing_name; }
	string getSex() const { return _sex; }
	int getAge() const { return _age; }
	string getCategory() const { return _category; }

private:
	int thing_id;
	string thing_name;
	string _sex;
	int _age;
	string _category;
};

class Node
{
private:
	Thing *theThing;
	Node * next;

public:
	Node(Thing *theObject)
		:theThing(theObject), next(0)
	{ }
	Node * getNext() { return next; }
	Thing * getThing() { return theThing; }
	void setNext(Node *nextNode)
	{
		next = nextNode;
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
	void create(Thing *);
	void insert(Thing*, int);
	Thing *find(int); 
	void repair(Thing *,int);
	bool remove(int);
	Node *getfirst() { return first; }
};


class ListItr
{
private:
	Node *current;
	ListMgr *theList;
public:
	ListItr(ListMgr *whichList)
		:current(0), theList(whichList)
	{ }
	Thing * getNext();
};

class AppClass
{
private:
	ListMgr * theList;
	int  menu();
	void addThing();
	void removeThing();
	void view();
	void repairThing();
	void createThing(int);
	void searchThing();
	void show(Thing*);
public:
	AppClass() { theList = new ListMgr(); }
	void run();
};