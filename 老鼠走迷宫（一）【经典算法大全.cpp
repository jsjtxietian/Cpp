#include<iostream>
#include<fstream> 

using namespace std;

int si , sj , ei , ej ;//start & end 
int maze[10][10];
int r,l ;
bool succeed = false;

bool visit(int , int );

int main() 
{
	ifstream in_file("input.txt");
	
	int temp;
	
	in_file >> r >> l >> si >> sj >> ei >> ej;
	
	for(int i = 0 ; i < r ; i++)
		for(int j = 0 ; j < l ; j++)
			in_file >> maze[i][j];
	
	for(int i = 0 ; i < r ; i++)
	{
		for(int j = 0 ; j < l ; j++)
		{
			if(maze[i][j] == 2)
				cout << "¨€";
			else
				cout << "  ";
		}
		cout << endl;
	}
			
	cout << endl; 
	
	if(visit(si,sj) == true)
		for(int i = 0 ; i < r ; i++)
		{
			for(int j = 0 ; j < l ; j++)
			{
				if(maze[i][j] == 2)
					cout << "¨€";
				else if ( maze[i][j] == 1)
					cout << "¡ó";
				else
					cout << "  ";
			}
			cout << endl;
		}
			
	else
		cout << "Can not find the path!" << endl;
	
	return 0;
}

bool visit(int i , int j)
{
	maze[i][j] = 1;
	
	if( i == ei && j == ej)
		succeed = true ;
	
	if( !succeed && maze[i][j+1] == 0 ) visit(i,j+1); 
	if( !succeed && maze[i+1][j] == 0 ) visit(i+1,j);
	if( !succeed && maze[i][j-1] == 0 ) visit(i,j-1);
	if( !succeed && maze[i-1][j] == 0 ) visit(i-1,j);
	
	if( succeed == false )	
		maze[i][j] = 0;
	return succeed;
}



