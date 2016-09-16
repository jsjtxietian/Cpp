#include <iostream>
#include <ctime>
#include <cstdlib> 

#define N 500000

using namespace std;

int main()
{
    int i , sum = 0;
    double x , y ;

    srand( (unsigned int)time(NULL) );

    for( i = 1 ; i < N ; i++)
    {
        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;
        if( x*x + y*y < 1 )
            sum++;
    }

    cout << "PI = " << (double)sum / N * 4 << endl;
    return 0;
}
