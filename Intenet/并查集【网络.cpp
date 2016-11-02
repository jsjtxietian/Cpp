//首先在地图上给你若干个城镇，这些城镇都可以看作点，
//然后告诉你哪些对城镇之间是有道路直接相连的。
//最后要解决的是整幅图的连通性问题。比如随意给你两个点，
//让你判断它们是否连通，或者问你整幅图一共有几个连通分支，
//也就是被分成了几个互相独立的块。像畅通工程这题，问还需要修几条路，
//实质就是求有几个连通分支。如果是1个连通分支，说明整幅图上的点都连起来了，
//不用再修路了；如果是2个连通分支，则只要再修1条路，从两个分支中各选一个点，
//把它们连起来，那么所有的点都是连起来的了；
//如果是3个连通分支，则只要再修两条路……
//以下面这组数据输入数据来说明
//4 2 
//1 3 4 3
//第一行告诉你，一共有4个点，2条路。下面两行告诉你，
//1、3之间有条路，4、3之间有条路。那么整幅图就被分成了-3-4和2两部分。
//只要再加一条路，把2和其他任意一个点连起来，
//畅通工程就实现了，那么这个这组数据的输出结果就是1。 

#include<iostream>
#include<cstring>

using namespace std;

int pre[1050];
bool t[1050]; //t用于标记独立块的根节点

int Find(int x)
{
	int r = x;
	while(pre[r] != r)
	{
		r = pre[r];
	}
	
	int i = x ;  //路径压缩 
	while(pre[i] != r)
	{
		int j = pre[i];
		pre[i] = r;
		i = j;
	}
	
	return r;
} 

void join(int x , int y)
{
	int ix = Find(x);
	int iy = Find(y);
	pre[ix] = iy;
}

int main()
{
	int N,M,a,b,i,j,ans;
	while(scanf("%d%d",&N,&M) && N)
	{
		for( i = 1 ; i <= N ; i++)
			pre[i] = i;
			
		for( i = 1 ; i <= M ; i++)
		{
			scanf("%d%d",&a,&b);
			join(a,b);
		}
		
		memset(t,0,sizeof(t));
		for( i = 1 ; i <= N ; i++)
			t[Find(i)] = 1 ; //标记根结点
		for( ans = 0 , i = 1 ; i <= N ; i++)
			if(t[i])
				ans++;
		printf("%d\n",ans-1); 
	}
}
