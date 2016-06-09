#include<iostream>
#include<fstream> 

using namespace std;

int si , sj , ei , ej ;//start & end 
int maze[10][10];
int r,l ;

void visit(int , int );

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
	cout<<endl; 
	
	visit(si,sj); 
	
	return 0;
}



void visit(int i , int j)
{
	int m, n ;
	maze[i][j] = 1;
	
	if( i == ei && j == ej)
	{
		for(int m = 0 ; m < r ; m++)
		{
			for(int n = 0 ; n < l ; n++)
			{
				if(maze[m][n] == 2)
					cout << "¨€";
				else if ( maze[m][n] == 1)
					cout << "¡ó";
				else
					cout << "  ";
			}
			cout << endl;
		}
		cout << endl;
	}
	
	if( maze[i][j+1] == 0 ) visit(i,j+1); 
	if( maze[i+1][j] == 0 ) visit(i+1,j);
	if( maze[i][j-1] == 0 ) visit(i,j-1);
	if( maze[i-1][j] == 0 ) visit(i-1,j);
	
	maze[i][j] = 0;
}



