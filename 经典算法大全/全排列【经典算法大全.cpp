#include <iostream>

#define N 4

using namespace std; 

void perm(int * , int );

int main()
{
    int num[N+1];
    for( int i = 0 ; i <= N ; i++)
        num[i] = i;
    perm(num , 1);
}

void perm( int * num , int i)
{
    int j , k , tmp ;

    if( i < N)
    {
        for( j = i ; j <= N ; j++)
        {
            tmp = num[j];

            for( k = j ; k > i ; k--)
                num[k] = num[k-1];
            num[i] = tmp ;
            perm(num,i+1);

            for( k = i ; k < j ; k++)
              	num[k] = num[k+1];
            num[j] = tmp;
        }
    }
    else
    {
        for( j = 1 ; j <= N ; j++)
            cout << num[j] << " ";
        cout << endl;
    }
}
