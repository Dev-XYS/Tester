#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
using namespace std;
const int inf=1e9+7;
int n,m,ans;
int vis[55][55],mark[55][55],tot;
inline void dfs2(int x,int y,int t)
{
	if(x==n && y==m)
	{
		tot++;
		return;
	}
	vis[x][y]=1;
	if(x+1<=n && !vis[x+1][y])
	{
		if(!mark[x+1][y])	dfs2(x+1,y,t);
		else
		{
			if(t)	dfs2(x+1,y,t-1);
		}
	}
	if(y+1<=m && !vis[x][y+1])
	{
		if(!mark[x][y+1])	dfs2(x,y+1,t);
		else
		{
			if(t)	dfs2(x,y+1,t-1);
		}
	}
	vis[x][y]=0;
}
inline void dfs1(int x,int y,int t)
{
	if(x==n && y==m)
	{
		tot=0;
		dfs2(1,1,t);
		ans+=tot;
		return;
	}
	vis[x][y]=1;
	if(x+1<=n && !vis[x+1][y])
	{
		if(!mark[x+1][y])	dfs1(x+1,y,t);
		else
		{
			if(t)	dfs1(x+1,y,t-1);
		}
	}
	if(y+1<=m && !vis[x][y+1])
	{
		if(!mark[x][y+1])	dfs1(x,y+1,t);
		else
		{
			if(t)	dfs1(x,y+1,t-1);
		}
	}
	vis[x][y]=0;
}
int main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	int T,C,D,P;
	scanf("%d",&T);
	while(T--)
	{
		memset(vis,0,sizeof(vis));
		memset(mark,0,sizeof(mark));
		ans=0;
		scanf("%d%d%d%d%d",&n,&m,&C,&D,&P);
		for(int i=1;i<=C;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			mark[x][y]=1;
		}
		dfs1(1,1,D);
		cout<<(ans/2)%P<<endl;
	}
	return 0;
} 
