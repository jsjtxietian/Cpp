#include "Josephus.h"


int main()
{
	Driver* d = new Driver();
	d->run();
	system("pause");
	return 0;
}

void Driver::run()
{
	int N,S,M,K;
	cout << "现有N人围成一圈，从第S个人开始依此报数，报M的出局，再由下一人开始报数如此循环，直到剩下K个人为止\n"
		 << "请输入生死游戏的总人数N：";
	cin >> N;
	cout << "请输入游戏开始的位置S：";
	cin >> S;
	cout << "请输入死亡数字M：";
	cin >> M;
	cout << "请输入剩余的生者人数K:";
	cin >> K;

	Josephus *p = new Josephus(N, S, M, K);
	p->run();
}

void Josephus::run()
{
	head = new Node(1);         //建立链表
	Node* current =head , *previous = current;
	for (int i = 2; i <= N; i++)
	{
		current = new Node(i);
		previous->next = current;
		previous = current;
	}
	current->next = head;

	int death = 0;
	current = head;//定位到S准备开始
	for (int i = 1; i < S; i++)
	{
		current = current->next;
	}
		

	while (count() != K)
	{
		for (int i = 1; i < M; )
		{
			if (current->isAlive)
			{
				i++;
			}
			current = current->next;
		}
			
		while (current->isAlive == false)
			current = current->next;
		current->isAlive = false;
		death++;
		cout << "第" << death << "个死者的位置是:\t" << current->num  << endl;
		current = current->next;
	}

	cout << "最后剩下：\t" << K << "人" << '\n'
		<< "最后生者的位置为:\n" << endl;
	
	if (head->isAlive)
		cout << head->num << '\t';
	current = head->next;
	while (current != head)
	{
		if (current->isAlive)
			cout << current->num << '\t';
		current = current->next;
	}
}

int Josephus::count()
{
	int n = 0;

	if (head->isAlive)
	{
		n++;
	}
	Node* current = head->next;
	
	while (current != head)
	{
		if (current->isAlive)
			n++;
		current = current->next;
	}
	
	return n;
}

