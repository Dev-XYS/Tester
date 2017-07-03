#include <cstdio>
typedef long long ll;

struct path
{
	int to,next,num;
	ll v1,v2;
}g[4010];
int n,m,sz,l,r,tot;
int q[2010],pos[2010],last[110],fa[2010];
ll mod;
ll ans[2010];
ll G[2110][2110];
bool vis[2010];

int getint()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

ll getll()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

inline int abs(int x)
{
	return x>0?x:-x;
}

void swap(ll &a,ll &b)
{
	ll t=a;
	a=b;
	b=t;
}

void ins(int a,int b,ll v1,ll v2,int num)
{
	g[++tot].to=b;
	g[tot].next=last[a];
	last[a]=tot;
	g[tot].v1=v1;
	g[tot].v2=v2;
	g[tot].num=num;
}

void insert(int a,int b,ll v1,ll v2,int num)
{
	ins(a,b,v1,v2,num);
	ins(b,a,-v1,v2,-num);
}

void dfs(int x,int f)
{
	if(pos[x]!=0)
	{
		sz++;
		for(int i=pos[x];i<=r;i++)
		{
			G[sz][abs(q[i])]=q[i]>0?g[q[i]*2].v2:-g[-q[i]*2].v2;
			G[sz][m+1]=(G[sz][m+1]+(q[i]>0?g[q[i]*2].v1:g[-q[i]*2+1].v1))%mod;
		}
		return;
	}
	if(fa[x]!=0) return;
	fa[x]=f;
	for(int i=last[x];i>0;i=g[i].next)
	{
		int t=g[i].to;
		if(t==fa[x]) continue;
		q[++r]=g[i].num;
		pos[x]=r;
		dfs(t,x);
		r--;
	}
	pos[x]=0;
}

void extgcd(ll a,ll b,ll &x,ll &y)
{
	if(b==0)
	{
		x=1,y=0;
		return;
	}
	extgcd(b,a%b,y,x);
	y-=a/b*x;
}

ll gcd(ll a,ll b)
{
	return b==0?a:gcd(b,a%b);
}

ll lcm(ll a,ll b)
{
	return a/gcd(a,b)*b;
}

ll getNi(ll a)
{
	ll x,y;
	extgcd(a,mod,x,y);
	return (x%mod+mod)%mod;
}

int Gauss()
{
	int col=1;
    for (int k=1;k<=sz&&col<=m;k++,col++)
	{
        int j=k;
        while(G[j][col]==0&&j<=sz) j++;
        if(j!=k)
		{
			for(int i=k;i<=m+1;i++) swap(G[k][i],G[j][i]);
		}
		if(G[k][col]==0)
		{
			k--;
			continue;
		}
        for(int i=k+1;i<=sz;i++)
		{
            if(G[i][col]!=0)
			{
                ll Lcm=lcm(G[k][col],G[i][col]);
                ll ta=Lcm/abs(G[i][col]),tb=Lcm/abs(G[k][col]);
                if(G[i][col]*G[k][col]<0) tb=-tb;
                for(int j=col;j<=m+1;j++)
					G[i][j]=((ta*G[i][j]-tb*G[k][j])%mod+mod)%mod;
            }
        }
    }
    for(int i=m;i;i--)
	{
    	ll t=G[i][m+1];
        for(int j=i+1;j<=m;j++) t-=G[i][j]*ans[j];
        ans[i]=t*getNi(G[i][i])%mod;
    }
    return 0;
}

int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	n=getint(),m=getint(),mod=getll();
	tot=1;
	for(int i=1;i<=m;i++)
	{
		int x=getint(),y=getint();
		ll a=getll(),b=getll();
		insert(x,y,a,b,i);
	}
	sz=n;
	for(int i=1;i<=n;i++)
	{
		for(int j=last[i];j>0;j=g[j].next)
			G[i][abs(g[j].num)]=g[j].num>0?1:-1;
		G[i][m+1]=0;
	}
	l=1,r=0;
	dfs(1,-1);
	Gauss();
	for(int i=1;i<=m;i++) printf("%I64d\n",(ans[i]%mod+mod)%mod);
	return 0;
}
