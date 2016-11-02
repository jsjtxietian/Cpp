//����һ��������n��С����Ҫʵ��n��С��֮��ĵ������ܹ��໥��ͨ��
//�����������n��С��֮��ĵ�����ʹ�ܹ��������͡������һ���ܹ�����Ҫ�����۷����� 

#include"graph.h"

int main()
{
	Driver t;
	t.run();
    return 0;
}

void Driver::run()
{
	cout << "**     �������ģ��ϵͳ     **" << '\n'
		 << "==============================="<< '\n'
		 << "**     A--������������      **" << '\n'
	  	 << "**     B--��ӵ����ı�      **" << '\n'
	 	 << "**     C--������С������    **" << '\n'
		 << "**     D--��ʾ��С������    **" << '\n'
		 << "**     E--�˳�����          **" << '\n'
		 << "==============================" << endl;

	char command;

	for (;;)
	{
		cout << "��ѡ�����: ";
		cin >> command;
		switch (command)
		{
		case 'A':
			addPoint();
			break;
		case 'B':
			addEdge();
			break;
		case 'C':
			kruskal();
			break;
		case 'D':
			output();
			break;
		case 'E':
			exit(1);
		default:
			cout << "δʶ���ָ�\n";
			continue;
		}
	}
}

void Driver::addPoint()
{
	cout << "��������������������:\n";
	char u ;

	while ( cin >> u )
	{
		if (!isalpha(u))
		{
			cout << "��������ĸлл����!\n";
			continue;
		}
		_point.push_back(u);

		if (getchar() == '\n') //���������\n��β
			break;
	}
}

void Driver::addEdge()
{
	cout << "�����������㼰��(���룿 �� 0ֹͣ):\n";
	char s, e;
	int w;
	cin >> s >> e >> w;
	while (s != '?')
	{
		Edge temp;
		if (s > e)       // ���Ͻڵ������ a-b-c-d
		{
			char c = s;
			s = e;
			e = c;
		}
		temp.point.start = s;
		temp.point.end = e;
		temp.weight = w;
		_edge.push(temp);

		cout << "�����������㼰��:\n";
		cin >> s >> e >> w;
	}

}

void Driver::kruskal()
{
	for (auto i : _point)
		_father[i] = i;

	while ( _result.size() < _point.size()-1 )
	{
		Edge temp = _edge.top();
		//todo
		char fs = find(temp.point.start);
		char fe = find(temp.point.end);
		if (fs == fe)
			continue;
		else
		{
			_result.push_back(temp);
			join(temp.point.end, temp.point.start);
		}
		_edge.pop();
	} 

	cout << "������С��������" << endl;
}

void Driver::output()
{
	cout << "��С�������Ķ��㼰��Ϊ:" << endl;

	for (auto i : _result)
	{
		cout << i.point.start << "-<" << i.weight << ">-" << i.point.end << '\t';
	}
	cout << endl;
}

void Driver::join(char a, char b)
{
	int fa = find(a);
	int fb = find(b);
	if (fa != fb)
		_father[fa] = fb;
}

char Driver::find(char t)
{
	char r = t;
	while (_father[r] != r)
	{
		r = _father[r];
	}

	char i = r;
	while (_father[i] != r)  //·��ѹ��
	{
		char j = _father[i];
		_father[i] = r;
		i = j;
	}
	
	return r;
}

