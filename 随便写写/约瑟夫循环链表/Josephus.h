#include<iostream>

using namespace std;

typedef struct node
{
	int num;
	bool isAlive;
	struct node* next;

	node(int n)
		:num(n), next(nullptr),isAlive(true)
	{ }
}Node;

class Driver
{
public:
	void run();
};

class Josephus
{
public:
	Josephus(int n,int s,int m,int k)
		:N(n),S(s),M(m),K(k),head(nullptr)
	{}
	void run();
	int count();
private:
	int N,S,M,K;
	Node* head;
};