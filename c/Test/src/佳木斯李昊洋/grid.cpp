#include<cstdio>
#include<cstring>
#define gm 51
using namespace std;
int T;
int n,m,c,d,mod;
bool sp[gm][gm],used[gm][gm];
int ans,last;
void dfs2(int x,int y,int cnt)
{
	if(sp[x][y]) ++cnt;
	if(last+cnt>d) return;
	if(x==n&&y==m)
	{
		++ans;
		return;
	}
	if(x!=n&&!used[x+1][y]) dfs2(x+1,y,cnt);
	if(y!=m&&!used[x][y+1]) dfs2(x,y+1,cnt);
}
void dfs1(int x,int y,int cnt)
{
	if(sp[x][y]) ++cnt;
	if(x==n&&y==m)
	{
		last=cnt;
		dfs2(1,1,0);
		return;
	}
	used[x][y]=1;
	if(x!=n) dfs1(x+1,y,cnt);
	if(y!=m) dfs1(x,y+1,cnt);
	used[x][y]=0;
}
int main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d%d",&n,&m,&c,&d,&mod);
		memset(sp,0,sizeof sp);
		for(int i=1;i<=c;++i)
		{
			int x,y; scanf("%d%d",&x,&y);
			sp[x][y]=1;
		}
		ans=0;
		dfs1(1,1,0);
		printf("%d\n",(ans>>1)%mod);
	}
	return 0;
}
