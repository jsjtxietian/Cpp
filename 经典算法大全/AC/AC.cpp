#include"AC.h"


int main(int argc, char **argv)
{
	if (argc < 3)
	{
		cout << ":)" << endl;
		exit(1);
	}

	ifstream in(argv[1]);
	if (!in.is_open())
	{
		cout << ":(" << endl;
		exit(1);
	}

	vector<string> word;
	for (int i = 2; i < argc; i++)
		word.push_back(argv[i]);

	Node* root = new Node();
	createTrie(word, root);
	createFail(root);

	char buffer[MAX];
	while (!in.eof())
	{
		in.getline(buffer, MAX);
		query(root, buffer);
	}

	return 0;
}

void createTrie(vector<string>& word, Node* root)
{
	for (auto str : word)
	{
		Node* pre = root;
		for (int i = 0; i < str.size(); i++)
		{
			int index = str[i] - 'a';
			if (pre->next[index] == NULL)
				pre->next[index] = new Node(str[i]);
			pre = pre->next[index];
		}
		pre->isEnd = true;
	}
}

void createFail(Node* root)
{
	Node* queue[MAX];
	int head = 0, tail = 0;
	queue[head++] = root;
	root->fail = nullptr;

	while (head != tail)
	{
		Node* temp = queue[tail++];
		for (int i = 0; i < NUM; i++)
		{
			if (temp->next[i] != nullptr)
			{
				if (temp == root)
					temp->next[i]->fail = root;
				else
				{
					Node* p = temp->fail;
					while (p->next[i] == nullptr && p != root)
						p = p->fail;
					p = p->next[i];
					temp->next[i]->fail = (p==nullptr) ? root : p ;
				}
				queue[head++] = temp->next[i];
			}
		}
	}
	
}

void query(Node *root,char *str)
{
	char *ptr = str;
	Node *current = root;

	while (*ptr != '\n' && *ptr != '\0')
	{
		int i = *ptr - 'a';
		if (current->next[i] != nullptr)
		{
			current = current->next[i];
			while (current != root)
			{
				if (current->isEnd)
				{
	//				cout << *ptr << endl;
					current = current->fail; 
				}
				else
				{
					if (*(ptr + 1) == '\n' || *(ptr + 1) == '\0')
						return;
					int index = *(++ptr) - 'a';
					if (current->next[index] == nullptr)
						current = current->fail;
					else
						current = current->next[index];
				}
			}
		}
		ptr++;
	}
}
