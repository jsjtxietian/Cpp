#include "maze.h"

int main()
{                         
	cout << "请输入迷宫的长和宽：";   //处理输入数据
	cin >> m >> n;
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			maze[i][j] = '*';
	cout << "请依次输入迷宫状态（1表示墙壁，0表示可通行）:\n";
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			cin >> maze[i][j];
	Vec2 start;
	cout << "请输入起点\n";
	cin >> start.x >> start.y ;

	if (search(start.x , start.y))
		output();
	else
		cout << "没有终点，出不去啊！" << endl;
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
	cout << "迷宫地图:\n";             //输出迷宫
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << maze[i][j] << '\t';
		cout << endl;
	}
	while (!buffer.empty())        //输出路径
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
