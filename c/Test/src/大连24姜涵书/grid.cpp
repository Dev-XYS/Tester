#include<cmath>
#include<cctype>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define lol long long
#define ns namespace
const int M = 111;
int p,res;
int T,n,m,c,d;
int a[M][M];

void dfs2(int x,int y,int s)
{
	if(s > d) return;
	if(x==n && y==m)
	{
		++res;
		res %= p;
		return;
	}
	int pr = a[x][y];
	a[x][y] = 1;
	if(y+1<=m && a[x][y+1] != 1)
	{
		dfs2(x,y+1,a[x][y+1]==-1 ? s+1:s);
	}
	if(x+1<=n && a[x+1][y] != 1)
	{
		dfs2(x+1,y,a[x+1][y]==-1 ? s+1:s);
	}
	a[x][y] = pr;
	return;

}
void dfs1(int x,int y,int s)
{
	if(s > d) return;
	if(x==n && y==m)
	{
		dfs2(2,1,a[2][1]==-1 ? s+1:s);
		return;
	}
	int pr = a[x][y];
	a[x][y] = 1;
	if(y+1<=m && a[x][y+1] != 1)
	{
		dfs1(x,y+1,a[x][y+1]==-1 ? s+1:s);
	}
	if(x+1<=n && a[x+1][y] != 1)
	{
		dfs1(x+1,y,a[x+1][y]==-1 ? s+1:s);
	}
	a[x][y] = pr;
	return;
}

int main()
{
#ifdef shorn
	freopen("grid2.in","r",stdin);
#else
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
#endif
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d%d",&n,&m,&c,&d,&p);
		res = 0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
				a[i][j] = 0;
		}
		for(int i=1;i<=c;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			a[x][y] = -1;
		}
		dfs1(1,2,a[1][2]==-1 ? 1 : 0);
		printf("%d\n",(res % p + p) % p);
	}
	return 0;
}
