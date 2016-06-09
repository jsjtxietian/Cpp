#include <iostream>
#include <iomanip>
#define N 1000
using namespace std;

int main()
{
    int i , j ;
    int prime[N+1];

    for( i = 2 ; i <= N ; i++)
        prime[i] = 1 ;

    for( i = 2 ; i * i <= N ; i++)
    {
        if( prime[i] == 1 )
        {
            for( j = 2 * i ; j <= N ; j++)
            {
                if( j % i == 0 )
                    prime[j] = 0;
            }
        }
    }

    for( i = 2 ; i < N ; i++)
    {
        if( prime[i] == 1)
        {
            cout << setw(4) << i << ( i % 16 == 0 ? "\n" : " " );
        }
    }

    cout<<endl;
    return 0;
}
