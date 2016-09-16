#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

void compare(int [] , int , int , int );
void eightcoins(int [] );

int main()
{
    int coins[8];
    int i;

    srand( time(NULL) );

    for( int j = 0 ; j < 8 ; j++)
        coins[j] = 10;

    cout << "Input the weight of the fake coin"
         << ">10 || <10 :" << endl;
    cin >> i ;
    coins[ rand() % 8 ] = i ;

    eightcoins(coins);

    cout << "\nShow the weight of each coin:"<<endl;
    for( int j = 0 ; j < 8 ; j++)
        cout << coins[j] << ' ';

    return 0;
}

void compare( int coins[] , int i , int j , int k )
{
    if( coins[i] > coins[k] )
        cout << "¼Ù±Ò " << i+1 << " ½ÏÖØ";
    else
        cout << "¼Ù±Ò " << j+1 << " ½ÏÇá";
}

void eightcoins( int coins[])
{
    if( coins[0]+coins[1]+coins[2] ==
        coins[3]+coins[4]+coins[5] )
    {
        if( coins[6] > coins[7] )
            compare( coins , 6 , 7 , 0);
        else
            compare( coins , 7 , 6 , 0);
    }
    else if (coins[0]+coins[1]+coins[2] >
             coins[3]+coins[4]+coins[5] )
    {
      if(coins[0]+coins[3] == coins[1]+coins[4])
          compare(coins, 2, 5, 0);
      else if(coins[0]+coins[3] > coins[1]+coins[4])
          compare(coins, 0, 4, 1);
      if(coins[0]+coins[3] < coins[1]+coins[4])
          compare(coins, 1, 3, 0);
    }
    else
    {
      if(coins[0]+coins[3] == coins[1]+coins[4])
          compare(coins, 5, 2, 0);
      else if(coins[0]+coins[3] > coins[1]+coins[4])
          compare(coins, 3, 1, 0);
      if(coins[0]+coins[3] < coins[1]+coins[4])
          compare(coins, 4, 0, 1); 
    }

}

