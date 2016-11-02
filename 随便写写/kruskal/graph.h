#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

typedef struct vec2
{
	char start;
	char end;
}Vec2;

typedef struct edge
{
	Vec2 point;
	int weight;
	friend bool operator< (const struct edge& a, const struct edge& b)
	{
		return a.weight > b.weight;
	}
}Edge;

class Driver
{
public:
	void run();

private:
	void addPoint();
	void addEdge();
	void kruskal();
	void output();

	void join(char ,char );
	char find(char);

	priority_queue<Edge> _edge; //��
	vector<char> _point;         //��
	vector<Edge> _result;

	char _father[100];        //���鼯
};

