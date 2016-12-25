#pragma once

#define NUM 26
#define MAX 256

#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

typedef struct node
{
	struct node* next[NUM];
	struct node* fail;
	char key;
	bool isEnd;

	node(char in = NULL)
		:fail(nullptr),key(in),isEnd(false)
	{
		memset(next, 0, sizeof(next));
	}

}Node;

void createTrie(vector<string>&, Node*);
void createFail(Node*);
void query(Node *,char *);
