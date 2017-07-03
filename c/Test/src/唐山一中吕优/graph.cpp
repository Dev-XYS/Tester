#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 4005
typedef long long LL;
int pre[maxn],last[maxn],other[maxn],id[maxn],N,l;
int n,m,tot,father[maxn],num[maxn],dep[maxn];
LL mo,a[maxn][maxn],A[maxn],B[maxn];
bool vis[maxn];
struct edge 
{
	int x,y,id;
}e[maxn];

inline int read(void)
{
	int x=0;
	char ch=getchar();
	while (ch>'9'||ch<'0') ch=getchar();
	while (ch>='0'&&ch<='9') 
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x;
}

void connect(int x,int y,int z,LL a,LL b)
{
	l++;
	pre[l]=last[x];
	last[x]=l;
	other[l]=y;
	id[l]=z;
	A[l]=a;
	B[l]=b;
}

void dfs(int u,int fa)
{
	vis[u]=1;
	for (int p=last[u];p;p=pre[p])
	{
		int v=other[p];
		if (v==fa) continue;
		if (vis[v]) 
		{
			if (dep[v]>dep[u]) continue;
			tot++;
			a[tot][id[p]]=B[p];
			a[tot][N+1]+=A[p];
			a[tot][N+1]-=a[tot][N+1]>=mo?mo:0;
			int tmp=u;
			while (tmp!=v) 
			{
				a[tot][id[num[tmp]]]=B[num[tmp]];
				a[tot][N+1]+=A[num[tmp]];
				a[tot][N+1]-=a[tot][N+1]>=mo?mo:0;
				tmp=father[tmp];
			}
			continue;
		}
	//	if (tot==N) return;
		dep[v]=dep[u]+1;
		father[v]=u;
		num[v]=p;
		dfs(v,u);
	//	if (tot==N) return;
	}
}

LL muilty(LL x,LL y)
{
	LL ans=0;
	for (;y>0;y>>=1) 
	{
		if (y&1) ans=(ans+x)%mo;
		x=(x+x)%mo;
	}
	return ans;
}

LL power(LL x,LL b)
{
	LL ans=1;
	for (;b>0;b>>=1) 
	{
		if (b&1) ans=muilty(ans,x);
		x=muilty(x,x);
	}
	return ans;
}

void gauss(void)
{
	for (int i=1;i<=N;i++) 
	{
		int r=i;
		for (int j=i+1;j<=tot;j++)
			if (a[r][i]<a[j][i]) r=j;
		if (r!=i)
			for (int j=i;j<=N+1;j++) swap(a[r][j],a[i][j]);
		if (a[i][i]==0) {puts("WA");return;}
		LL inv=power(a[i][i],mo-2);
		for (int j=i+1;j<=tot;j++)
		{
			LL f=muilty(inv,a[j][i]);
			for (int k=i;k<=N+1;k++)
			{
				a[j][k]-=muilty(f,a[i][k]);
				a[j][k]+=a[j][k]<0?mo:0;
			}
		}
	}
	for (int i=N;i>=1;i--) 
	{
		a[i][i]=muilty(a[i][N+1],power(a[i][i],mo-2));
		for (int j=N-1;j>=1;j--) 
		{
			a[j][N+1]-=muilty(a[i][i],a[j][i]);
			a[j][N+1]+= a[j][N+1]<0?mo:0;
		}
	}
}

int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	n=read();m=read();scanf("%I64d",&mo);
	N=m+m;
	for (int i=1;i<=m;i++) 
	{
		e[i].x=read();e[i].y=read();
		int aa=read(),bb=read();
		e[i].id=i;
		connect(e[i].x,e[i].y,i*2-1,aa,bb);
		connect(e[i].y,e[i].x,i*2,mo-aa,bb);
		a[i][i*2-1]=a[i][i*2]=1;
	}
	for (int i=1;i<=n;i++)	
		for (int p=last[i];p;p=pre[p])
			a[m+i][id[p]]=1;
	tot=n+m;
	dfs(1,-1);
	gauss();
	for (int i=1;i<=m;i++)
	{
		int o=e[i].id;
		if (a[2*o-1][2*o-1]>=0) printf("%I64d\n",a[2*o-1][2*o-1]);
		else printf("%I64d\n",a[2*o][2*o]);
	}
	return 0;
}