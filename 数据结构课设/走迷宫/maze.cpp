#include "maze.h"

int main()
{                         
	cout << "�������Թ��ĳ��Ϳ�";   //������������
	cin >> m >> n;
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			maze[i][j] = '*';
	cout << "�����������Թ�״̬��1��ʾǽ�ڣ�0��ʾ��ͨ�У�:\n";
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			cin >> maze[i][j];
	Vec2 start;
	cout << "���������\n";
	cin >> start.x >> start.y ;

	if (search(start.x , start.y))
		output();
	else
		cout << "û���յ㣬����ȥ����" << endl;
}

void output()
{
	stack<Vec2> buffer;
	while (!path.empty())
	{
		Vec2 temp = path.top();
		buffer.push(temp);
		path.pop();
	}
	cout << "�Թ���ͼ:\n";             //����Թ�
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << maze[i][j] << '\t';
		cout << endl;
	}
	while (!buffer.empty())        //���·��
	{
		Vec2 temp = buffer.top();
		buffer.pop();
		cout << " <" << temp.x << "," << temp.y << ">";
		if (buffer.size() != 0)
			cout << " --->";
		
	}
	cout << endl;
}

bool search(int x , int y)
{
	Vec2 s = {x,y};
	path.push(s);
	maze[x][y] = 'x';

	if ( (x == m && y != 1) || (y == n && x != 1) )
		succeed = true;

	if ( maze[x - 1][y] == '0' && !succeed )
		search(x - 1, y);
	if ( maze[x + 1][y] == '0' && !succeed)
		search(x + 1, y);
	if ( maze[x][y - 1] == '0' && !succeed)
		search(x, y - 1);
	if ( maze[x][y + 1] == '0' && !succeed)
		search(x, y + 1);	
		
	if (!succeed)
	{
		path.pop();
		maze[x][y] = '0';
	}
		

	return succeed;
}
