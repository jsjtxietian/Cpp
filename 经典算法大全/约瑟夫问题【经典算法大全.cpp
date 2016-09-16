#include <iostream>

#define N 41 
#define M 3

using namespace std;

int main()
{
    int man[N] = {0};
    int count = 1 ;
    int i = 0 , pos = -1 ;
    int alive = 0;
    
    while( count <= N)
    {
        do
        {
            pos = ( pos + 1 ) % N ;
            if( man[pos] == 0 )
                i++;
            if(i == M)
            {
                i = 0 ;
                break ;
            }
        }while(1);
        
        man[pos] = count ;
        count++;
    }
    
    cout << "约瑟夫排列：";
    for( i = 0 ; i < N ; i++)
        cout << man[i] << " ";
    cout << "你想救多少人？\n";
    cin >> alive ;
    for( i = 0 ; i < N ; i++)
    {
        if( N - man[i] + 1 > alive )
            cout << "D";
        else
            cout << "L";
        if( (i+1) % 5 == 0 )
            cout << "  ";
    }
    cout << endl;
    return 0;
}
