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
	cout << "����N��Χ��һȦ���ӵ�S���˿�ʼ���˱�������M�ĳ��֣�������һ�˿�ʼ�������ѭ����ֱ��ʣ��K����Ϊֹ\n"
		 << "������������Ϸ��������N��";
	cin >> N;
	cout << "��������Ϸ��ʼ��λ��S��";
	cin >> S;
	cout << "��������������M��";
	cin >> M;
	cout << "������ʣ�����������K:";
	cin >> K;

	Josephus *p = new Josephus(N, S, M, K);
	p->run();
}

void Josephus::run()
{
	head = new Node(1);         //��������
	Node* current =head , *previous = current;
	for (int i = 2; i <= N; i++)
	{
		current = new Node(i);
		previous->next = current;
		previous = current;
	}
	current->next = head;

	int death = 0;
	current = head;//��λ��S׼����ʼ
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
		cout << "��" << death << "�����ߵ�λ����:\t" << current->num  << endl;
		current = current->next;
	}

	cout << "���ʣ�£�\t" << K << "��" << '\n'
		<< "������ߵ�λ��Ϊ:\n" << endl;
	
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

