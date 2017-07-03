#include <cstdio>
#include <algorithm>
#include <cstring>
#define MN 52
using namespace std;
int t,n,m,p,q,mod,ans;
int f[2][MN][MN][MN],l[MN<<1],r[MN<<1];
bool u[MN][MN];

inline int read()
{
	int n=0,f=1; char c=getchar();
	while (c<'0' || c>'9') {if(c=='-')f=-1; c=getchar();}
	while (c>='0' && c<='9') {n=n*10+c-'0'; c=getchar();}
	return n*f;
}

int main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	register int i,j,k,o,x,y,g,lt;
	t=read();
	while (t--)
	{
		n=read(); m=read(); p=read(); q=read(); mod=read();
		ans=0;
		memset(u,0,sizeof(u));
		for (i=1;i<=p;++i) x=read(),y=read(),u[x][y]=true;
		for (i=x=y=1;i<=n+m-1;++i,++x,++y) l[i]=1+max(0,x-n),r[i]=min(y,m);
		f[0][1][2][u[1][2]+u[2][1]]=1%mod;
//		for (i=1;i<=n+m-1;++i) printf("%d %d\n",l[i],r[i]);
		for (i=3,g=1;i<n+m-1;++i,g^=1)
		{
			memset(f[g],0,sizeof(f[g]));
			for (j=l[i];j<r[i];++j)
				for (k=j+1;k<=r[i];++k)
					for (o=lt=u[i-j+1][j]+u[i-k+1][k];o<=q;++o)
					{
						f[g][j][k][o]=(f[g^1][j-1][k-1][o-lt]+f[g^1][j-1][k][o-lt]+f[g^1][j][k][o-lt])%mod;
						if (j<k-1) {f[g][j][k][o]+=f[g^1][j][k-1][o-lt]; if (f[g][j][k][o]>=mod) f[g][j][k][o]-=mod;}
					}
		}
		for (i=0;i<=q;++i) {ans+=f[g^1][l[n+m-2]][r[n+m-2]][i]; if (ans>=mod) ans-=mod;}
		memset(f,0,sizeof(f));
//		printf("%d\n",f[g^1][l[n+m-2]][r[n+m-2]]);
		printf("%d\n",ans);
	}
}
