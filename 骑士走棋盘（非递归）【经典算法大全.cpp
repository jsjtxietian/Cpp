#include<iostream>
#include<iomanip>
using namespace std;

bool travel(int x , int y);

int board[8][8] = {0};

int main()
{
    int startx , starty ;
    cout << "�������ʼλ��"<<endl;
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
    //8������
    int ktmove1[8] = {-2,-1,1,2,2,1,-1,-2};
    int ktmove2[8] = {1,2,2,1,-1,-2,-2,-1};

    //������һ���ĳ�·
    int nexti[8] = {0};
    int nextj[8] = {0};
    //��¼���ڸ���
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

        //��̽8������
        for( k = 0 ; k < 8 ; k++)
        {
            tmpi = i + ktmove1[k];
            tmpj = j + ktmove2[k];

            //����Ǳ߽� ����
            if(tmpi < 0 || tmpj > 7 || tmpi > 7 || tmpj < 0)
                continue;
            //������������� ��¼����
            if( board[tmpi][tmpj] == 0 )
            {
                nexti[l] = tmpi;
                nextj[l] = tmpj;
                //���ߵķ���+1
                l++;
            }
        }

        count = l;
        //���ߵķ���Ϊ0������
        if(count == 0 )
            return false;
        else if(count == 1)
        {
            //ֻ��һ�����ߵķ���
            //����ֱ�������ٳ�·�ķ���
            min = 0;
        }
        else
        {
            //�ҳ���һ��λ�õĳ�·��
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
            //�ӿ��ߵķ�����Ѱ�����ٳ�·�ķ���
            for( l = 0 ; l < count ; l++)
            {
                if(exists[l] < tmp)
                {
                    tmp = exists[l];
                    min = l ;
                }
            }
        }
        //����С��·�ķ���
        i = nexti[min];
        j = nextj[min];
        board[i][j] = m ;
    }
    return true;
}

