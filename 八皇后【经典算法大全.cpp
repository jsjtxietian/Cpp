#include<iostream>

#define N 8
using namespace std;

int column[N+1];//ͬ���Ƿ��лʺ� 1��ʾ��
int rup[2*N + 1];//�����������Ƿ��лʺ�
int lup[2*N + 1];//�����������Ƿ��лʺ�
int queen[N+1] = {0};
int num;//�����

void backtrack(int );//�ݹ����

int main()
{
    int i ;
    num = 0 ;

    for( i = 1 ; i <= N ; i++)
        column[i] = 1;
    for( i = 1 ; i <= 2*N ; i++)
        rup[i] = lup[i] = 1;

    backtrack(1);

    return 0;
}

void showAnswer()
{
    int x , y ;
    cout << "The " << ++num << " of the Answer: " << endl;
    for( y = 1 ; y <= N ; y++)
    {
      for( x = 1 ; x <= N ; x++)
          if(queen[y] == x)
              cout << " Q";
          else
              cout << " .";
      cout << '\n' ;
    }
    cout << '\n' ;
}

void backtrack(int i )
{
    int j ;

    if( i > N)
        showAnswer();
    else
    {
        for(j = 1 ; j <= N ; j++)
        {
            if( column[j] == 1 && lup[i-j+N] == 1 && rup[i+j] == 1)
            {
                queen[i] = j;
                column[j] = rup[i+j] = lup[i-j+N] = 0;
                backtrack(i+1);
                column[j] = rup[i+j] = lup[i-j+N] = 1;
            }
        }
    }
}

