#pragma once

#include<iostream>
#include<memory>
#include<vector>
#include<string>

using namespace std;

class Node
{
public:
	typedef shared_ptr<Node> pNode;
	friend bool find(string name, shared_ptr<Node>& current, shared_ptr<Node>& result);

	string getName() { return _name; }
	void changeName(string name) { _name = name; }

	void listChild() 
	{
		for (auto i : _child)
			cout << i->getName() << ' ';
		cout << '\n' << endl;
	}

	Node(string name)
		:_name(name)
	{ }

	void add(string name)
	{
		pNode buffer = make_shared<Node>(name);
		_child.push_back(buffer);
	}

	void deleteChild()
	{
		_child.erase(_child.begin(), _child.end());
	}
	
private:
	string _name;
	vector<pNode> _child;
};

void createFamily(shared_ptr<Node> &);
void changeName(shared_ptr<Node>&);
bool find(string name, shared_ptr<Node>& current, shared_ptr<Node>& result);
void add(shared_ptr<Node>& );
void deleteChild(shared_ptr<Node>&);