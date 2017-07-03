#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read()
{
	int t=1,sum=0;char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') t=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		sum=sum*10+ch-'0',ch=getchar();
	return t*sum;
}
const int Max=55;
int f[2][Max][Max][Max],vis[Max<<1][Max<<1],n,m,C,D,mod;
void up(int &x,int y) { x+=y; if(x>=mod) x-=mod; }
bool check(int x,int y) { return vis[y][x-y+2]; }
void solve()
{
	int x,y,i,j,k,l,o=0,w;
	n=read(); m=read();
	memset(vis,0,sizeof vis);
	C=read(); D=read(); mod=read();
	for(i=1;i<=C;i++)
	{
		x=read(); y=read();
		vis[x][y]=1;
	}
	memset(f,0,sizeof f);
	f[o][1][1][0]=1;
	for(i=1;i<=n+m-2;i++)
	{
		o^=1;
		memset(f[o],0,sizeof f[o]);
		for(j=1;j<=n;j++)
			for(k=j;k<=n;k++)
				for(l=0;l<=D;l++) if(w=f[!o][j][k][l])
				{
					int ad;
					if(j<k&&j+1<=n&&k+1<=n)
					{
						ad=check(i,j+1)+check(i,k+1);
						if(l+ad<=D)
							up(f[o][j+1][k+1][l+ad],w);
					}
					if(k+1<=n)
					{
						ad=check(i,j)+check(i,k+1);
						if(l+ad<=D)
							up(f[o][j][k+1][l+ad],w);
					}
					if(j+1<k||(i==n+m-2&&j+1==n&&k==n))
					{
						ad=check(i,j+1)+check(i,k);
						if(l+ad<=D)
							up(f[o][j+1][k][l+ad],w);
					}
					if(j<k)
					{
						ad=check(i,j)+check(i,k);
						if(l+ad<=D)
							up(f[o][j][k][l+ad],w);	
					}
				}
	}
	int ans=0;
	for(i=0;i<=D;i++)
		up(ans,f[o][n][n][i]);
	printf("%d\n",ans);
}
int main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	int T=read();
	while(T--)
		solve();
	return 0;
}
