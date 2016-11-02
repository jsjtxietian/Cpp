//假设一个城市有n个小区，要实现n个小区之间的电网都能够相互接通，
//构造这个城市n个小区之间的电网，使总工程造价最低。请设计一个能够满足要求的造价方案。 

#include"graph.h"

int main()
{
	Driver t;
	t.run();
    return 0;
}

void Driver::run()
{
	cout << "**     电网造价模拟系统     **" << '\n'
		 << "==============================="<< '\n'
		 << "**     A--创建电网定点      **" << '\n'
	  	 << "**     B--添加电网的边      **" << '\n'
	 	 << "**     C--构造最小生成树    **" << '\n'
		 << "**     D--显示最小生成树    **" << '\n'
		 << "**     E--退出程序          **" << '\n'
		 << "==============================" << endl;

	char command;

	for (;;)
	{
		cout << "请选择操作: ";
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
			cout << "未识别的指令！\n";
			continue;
		}
	}
}

void Driver::addPoint()
{
	cout << "请依次输入各定点的名称:\n";
	char u ;

	while ( cin >> u )
	{
		if (!isalpha(u))
		{
			cout << "请输入字母谢谢合作!\n";
			continue;
		}
		_point.push_back(u);

		if (getchar() == '\n') //输入结束以\n结尾
			break;
	}
}

void Driver::addEdge()
{
	cout << "请输入两个点及边(输入？ ？ 0停止):\n";
	char s, e;
	int w;
	cin >> s >> e >> w;
	while (s != '?')
	{
		Edge temp;
		if (s > e)       // 保障节点的排序 a-b-c-d
		{
			char c = s;
			s = e;
			e = c;
		}
		temp.point.start = s;
		temp.point.end = e;
		temp.weight = w;
		_edge.push(temp);

		cout << "请输入两个点及边:\n";
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

	cout << "生成最小生成树！" << endl;
}

void Driver::output()
{
	cout << "最小生成树的顶点及边为:" << endl;

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
	while (_father[i] != r)  //路径压缩
	{
		char j = _father[i];
		_father[i] = r;
		i = j;
	}
	
	return r;
}

