/*
8kg at most
0  plum  4KG  NT$4500
1  apple  5KG  NT$5700
2  orange  2KG  NT$2250
3  strawberry  1KG  NT$1100
4  melom  6KG  NT$6700
*/

#include <iostream>
#include <string>

#define LIMIT 8 //weight limit
#define N     5 //types
#define MIN   1 //least weight

using namespace std;

typedef
struct body
{
    string name;
    int size ;
    int price ;
} object;

int main()
{
    int item[ LIMIT + 1 ] = { 0 };
    int value[ LIMIT + 1 ] = { 0 };
    int newvalue , i ,s, p ;

    object a[] = {
                      {"plum"       , 4 , 4500 },
                      {"apple"      , 5 , 5700 },
                      {"orange"     , 2 , 2250 },
                      {"strawberry" , 1 , 1100 },
                      {"melon"      , 6 , 6700 }
                 };
    for( i = 0 ; i < N ; i++)
        for( s = a[i].size ; s <= LIMIT ; s++)
        {
            p = s - a[i].size;
            newvalue = value[p] + a[i].price ;
            if( newvalue > value[s] )
            {
                value[s] = newvalue;
                item[s] = i;
            }
        }

    cout << "item\tprice" << endl;
    for ( i = LIMIT ; i >= MIN ; i = i - a[ item[i]].size )
    {
        cout << a[item[i]].name << '\t' << a[item[i]].price << endl;
    }

    return 0;
}
