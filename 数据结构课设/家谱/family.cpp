#include"family.h"


int main()
{
	cout << "**     ���׹���ϵͳ          **" << '\n'
		<< "================================" << '\n'
		<< "**     A--���Ƽ���            **" << '\n'
		<< "**     B--��Ӽ�ͥ��Ա        **" << '\n'
		<< "**     C--��ɢ�ֲ���ͥ        **" << '\n'
		<< "**     D--���ļ�ͥ��Ա����    **" << '\n'
		<< "**     E--�˳�����            **" << '\n'
		<< "================================" << endl;

	cout << "���Ƚ���һ�����ף�\n"
		<< "���������ȵ�����: ";
	string name;
	cin >> name;
	shared_ptr<Node> ancestor = make_shared<Node>(name);
	cout << "�˼��׵�������: " << ancestor->getName() << '\n' <<endl;
	
	do
	{
		char command;
		cout << "��ѡ��Ҫִ�еĲ���: ";
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
			cout << "��������ȷ��ָ�" << endl;
			continue;
		}

	} while (1);

	return 0;
}

void createFamily(shared_ptr<Node>& ancestor)
{
	cout << "������Ҫ������ͥ���˵�����: ";
	string name;
	cin >> name;
	
	shared_ptr<Node> father;
	while (!find(name, ancestor, father))
	{
		cout << "��������ȷ������ лл������";
		cin >> name;
	}

	cout << "������" << name << "�Ķ�Ů����: ";
	int count;
	cin >> count;

	cout << "����������" << name << "�Ķ�Ů����: ";
	while (count != 0)
	{
		string buffer;
		cin >> buffer;
		father->add(buffer);
		count--;
	}
	cout << name << " ����Ů�� ";
	father->listChild();
}

void changeName(shared_ptr<Node>& ancestor)
{
	cout << "�����������������Ŀǰ����: ";
	string name;
	cin >> name;

	shared_ptr<Node> self;
	while (!find(name, ancestor, self))
	{
		cout << "��������ȷ������ лл������";
		cin >> name;
	}

	cout << "��������ĺ������:  ";
	string currentName;
	cin >> currentName;
	self->changeName(currentName);

	cout << name << "�Ѹ���Ϊ" << currentName << '\n' << endl;
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
	cout << "������Ҫ��Ӷ�Ů��������: ";
	string name;
	cin >> name;

	shared_ptr<Node> self;
	while (!find(name, ancestor, self))
	{
		cout << "��������ȷ������ лл������ ";
		cin >> name;
	}

	cout << "�������Ů������: ";
	string sname;
	cin >> sname;
	self->add(sname);

	cout << name << " �ĵ�һ��������: ";
	self->listChild();
}

void deleteChild(shared_ptr<Node> &ancestor)
{
	cout << "������Ҫ��ɢ��ͥ���˵�����: ";
	string name;
	cin >> name;

	shared_ptr<Node> self;
	while (!find(name, ancestor, self))
	{
		cout << "��������ȷ������ лл������ " << endl;
		cin >> name;
	}

	cout << "Ҫ��ɢ��ͥ������: " << name << endl ;
	self->listChild();
	self->deleteChild();
}