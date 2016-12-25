#include"family.h"


int main()
{
	cout << "**     家谱管理系统          **" << '\n'
		<< "================================" << '\n'
		<< "**     A--完善家谱            **" << '\n'
		<< "**     B--添加家庭成员        **" << '\n'
		<< "**     C--解散局部家庭        **" << '\n'
		<< "**     D--更改家庭成员姓名    **" << '\n'
		<< "**     E--退出程序            **" << '\n'
		<< "================================" << endl;

	cout << "首先建立一个家谱！\n"
		<< "请输入祖先的姓名: ";
	string name;
	cin >> name;
	shared_ptr<Node> ancestor = make_shared<Node>(name);
	cout << "此家谱的祖先是: " << ancestor->getName() << '\n' <<endl;
	
	do
	{
		char command;
		cout << "请选择要执行的操作: ";
		cin >> command;
		cout << endl;

		switch (command)
		{
		case 'A':
			createFamily(ancestor);
			break;
		case 'B':
			add(ancestor);
			break;
		case 'C':
			deleteChild(ancestor);
			break;
		case 'D':
			changeName(ancestor);
			break;
		case 'E':
			exit(1);
		default:
			cout << "请输入正确的指令！" << endl;
			continue;
		}

	} while (1);

	return 0;
}

void createFamily(shared_ptr<Node>& ancestor)
{
	cout << "请输入要建立家庭的人的姓名: ";
	string name;
	cin >> name;
	
	shared_ptr<Node> father;
	while (!find(name, ancestor, father))
	{
		cout << "请输入正确的名字 谢谢合作：";
		cin >> name;
	}

	cout << "请输入" << name << "的儿女人数: ";
	int count;
	cin >> count;

	cout << "请依次输入" << name << "的儿女姓名: ";
	while (count != 0)
	{
		string buffer;
		cin >> buffer;
		father->add(buffer);
		count--;
	}
	cout << name << " 的子女是 ";
	father->listChild();
}

void changeName(shared_ptr<Node>& ancestor)
{
	cout << "请输入更改姓名的人目前姓名: ";
	string name;
	cin >> name;

	shared_ptr<Node> self;
	while (!find(name, ancestor, self))
	{
		cout << "请输入正确的名字 谢谢合作：";
		cin >> name;
	}

	cout << "请输入更改后的姓名:  ";
	string currentName;
	cin >> currentName;
	self->changeName(currentName);

	cout << name << "已更名为" << currentName << '\n' << endl;
}

bool find(string name, shared_ptr<Node>& current , shared_ptr<Node>& result)
{
	if (current->getName() == name)
	{
		result = current;
		return true;
	}	
	else
	{
		if (current->_child.size() != 0)
		{
			for (auto& i : current->_child)
			{
				if (find(name, i, result))
					return true;
			}
		}	
		return false;	
	}
}

void add(shared_ptr<Node>& ancestor)
{
	cout << "请输入要添加儿女的人姓名: ";
	string name;
	cin >> name;

	shared_ptr<Node> self;
	while (!find(name, ancestor, self))
	{
		cout << "请输入正确的名字 谢谢合作： ";
		cin >> name;
	}

	cout << "请输入儿女的姓名: ";
	string sname;
	cin >> sname;
	self->add(sname);

	cout << name << " 的第一代子孙是: ";
	self->listChild();
}

void deleteChild(shared_ptr<Node> &ancestor)
{
	cout << "请输入要解散家庭的人的姓名: ";
	string name;
	cin >> name;

	shared_ptr<Node> self;
	while (!find(name, ancestor, self))
	{
		cout << "请输入正确的名字 谢谢合作： " << endl;
		cin >> name;
	}

	cout << "要解散家庭的人是: " << name << endl ;
	self->listChild();
	self->deleteChild();
}