#include"Queen.h"

int main()
{
	vector<int> queen;
	cout << "请输入N皇后的N:\n" << endl;
	cin >> N;

	for (int i = 0; i < N; i++) //初始化
		queen.push_back(0);
	queen.push_back(0);  //1-8
	
	search(queen,1);
	cout << "共有" << Count << "种解法" << endl;
	system("pause");
	return 0;
}

bool conflict(vector<int> &queen , int index)
{
	for (int i = 1 ; i < index ; i++)
	{
		if (queen[i] == queen[index] 
		  || i+queen[i] == index + queen[index] 
		  || i - index == queen[i] - queen[index]
			)
			return true;
	}

	return false;
}

void print(vector<int> &queen)
{
	cout << '\n';
	for (int x = 1 ; x < queen.size(); x++)
	{
		for (int i = 1; i < queen[x]; i++)
			cout << "0 ";
		cout << "X ";
		for (int i = queen[x] ; i < queen.size()-1 ; i++)
			cout << "0 ";
		cout << endl;
	}
	cout << endl;
}

void search(vector<int> &queen , int current)
{
	if (current > N)
	{
		print(queen);
		Count++;
	}
	else
	{
		for (int j = 1; j <= N; j++)
		{
			queen[current] = j;
			if (!conflict(queen, current))
			{
				search(queen, current + 1);
			}
		}
	}
}