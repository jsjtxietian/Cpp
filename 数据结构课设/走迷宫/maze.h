#pragma once

#include<iostream>
#include<stack>
#include<vector>

#define MAX 100
using namespace std;

typedef struct vec2
{
	int x;
	int y;
}Vec2;

int m, n;
char maze[MAX][MAX];
stack<Vec2> path;
bool succeed = false;

bool search(int , int);
void output();