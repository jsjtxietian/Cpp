#include<iostream>
#include<iomanip>
using namespace std;

bool travel(int x , int y);

int board[8][8] = {0};

int main()
{
    int startx , starty ;
    cout << "请输入初始位置"<<endl;
    cin >> startx >> starty;

    if(travel(startx , starty))
        cout << "Succeed!"<<endl;
    else
        cout << "Failed!" << endl;

    for( int i = 0 ; i < 8 ; i++)
    {
        for(int j = 0 ; j < 8 ; j++)
            cout << setw(2) <<board[i][j] << ' ';
        cout << '\n';
    }

    return 0;
}

bool travel(int x , int y)
{
    //8个方向
    int ktmove1[8] = {-2,-1,1,2,2,1,-1,-2};
    int ktmove2[8] = {1,2,2,1,-1,-2,-2,-1};

    //测试下一步的出路
    int nexti[8] = {0};
    int nextj[8] = {0};
    //记录出口个数
    int exists[8] = {0};
    int i,j,k,m,l;
    int tmpi,tmpj;
    int count , min , tmp ;

    i = x ;
    j = y ;
    board[i][j] = 1;

    for( m = 2 ; m <= 64 ; m++)
    {
        for( l = 0 ; l < 8 ; l++)
            exists[l] = 0;

        l = 0 ;

        //试探8个方向
        for( k = 0 ; k < 8 ; k++)
        {
            tmpi = i + ktmove1[k];
            tmpj = j + ktmove2[k];

            //如果是边界 不走
            if(tmpi < 0 || tmpj > 7 || tmpi > 7 || tmpj < 0)
                continue;
            //如果这个方向可走 记录下来
            if( board[tmpi][tmpj] == 0 )
            {
                nexti[l] = tmpi;
                nextj[l] = tmpj;
                //可走的方向+1
                l++;
            }
        }

        count = l;
        //可走的方向为0，返回
        if(count == 0 )
            return false;
        else if(count == 1)
        {
            //只有一个可走的方向
            //所以直接是最少出路的方向
            min = 0;
        }
        else
        {
            //找出下一个位置的出路数
            for( l = 0 ; l < count ; l++)
            {
                for( k = 0 ; k < 8 ; k++)
                {
                    tmpi = nexti[l] + ktmove1[k];
                    tmpj = nextj[l] + ktmove2[k];
                    if( tmpi < 0 || tmpj < 0 || tmpi > 7 || tmpj > 7)
                        continue;
                    if(board[tmpi][tmpj] == 0)
                        exists[l] ++ ;
                }
            }
            tmp = exists[0];
            min = 0;
            //从可走的方向中寻找最少出路的方向
            for( l = 0 ; l < count ; l++)
            {
                if(exists[l] < tmp)
                {
                    tmp = exists[l];
                    min = l ;
                }
            }
        }
        //走最小出路的方向
        i = nexti[min];
        j = nextj[min];
        board[i][j] = m ;
    }
    return true;
}

