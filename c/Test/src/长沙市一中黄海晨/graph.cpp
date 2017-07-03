#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
using namespace std;
inline LL read()
{
	LL t=1,sum=0;char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') t=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		sum=sum*10+ch-'0',ch=getchar();
	return t*sum;
}
const int _N=1e2+10,_M=2e3+10;
int fir[_N],cro[_N],fa[_N],dep[_N],vis[_N],cnt,tot,n,m;
LL d[_N],cb[_N],C[_N],A[_N][_N],B[_N],Ans[_M],mod;
LL mul(LL a,LL b)
{
	LL ans=0;
	while(a)
	{
		if(a&1) ans+=b; 
		if(ans>=mod) ans-=mod;
		b<<=1; if(b>=mod) b-=mod;
		a>>=1;
	}
	return ans;
}
LL fpm(LL x,LL y)
{
	LL ans=1;
	for(;y;y>>=1,x=mul(x,x))
		if(y&1)
			ans=mul(ans,x);
	return ans;
}
struct edge
{
	int to,nxt,id;
	LL A,B;
	edge () {}
	edge (int x,int y,LL w1,LL w2,int l)
	{
		to=y; nxt=fir[x]; 
		A=w1; B=w2; id=l;
		fir[x]=cnt;
	}
}e[_M<<1];
void dfs(int x,int p)
{
	int i,j,v;  vis[x]=1;
	for(i=fir[x];i;i=e[i].nxt)
		if(e[i].to!=p)
		{
			v=e[i].to;
			if(!vis[v])
			{
				fa[v]=x;
				dep[v]=dep[x]+1;
				d[v]=(d[x]+e[i].A)%mod;
				cro[v]=++tot; cb[v]=e[i].B;
				dfs(v,x);
				A[x][cro[v]]=(A[x][cro[v]]+1)%mod;
			}		
			else if(dep[v]<dep[x])
			{
				int u=x; LL inv=fpm(e[i].B,mod-2);
				while(u!=v)
				{
					A[x][cro[u]]=(A[x][cro[u]]-mul(cb[u],inv)+mod)%mod;
					A[v][cro[u]]=(A[v][cro[u]]+mul(cb[u],inv))%mod;
					u=fa[u];
				}
				LL sum=(d[x]-d[v]+e[i].A+mod)%mod;
				B[x]=(B[x]+mul(sum,inv))%mod;
				B[v]=(B[v]-mul(sum,inv)+mod)%mod;
			}
		}
	if(x!=1)
		A[x][cro[x]]=(A[x][cro[x]]-1+mod)%mod;
}
void gauss()
{
	int i,j,k;
	for(i=1;i<n;i++)
	{
		for(j=i;j<=n;j++)
			if(A[j][i])
				break;
		if(j!=i)
			swap(A[i],A[j]),swap(B[i],B[j]);
		LL inv=fpm(A[i][i],mod-2);
		for(j=1;j<=n;j++)
			if(i!=j&&A[j][i])
			{
				LL tmp=mul(A[j][i],inv);
				for(k=1;k<n;k++)
					A[j][k]=(A[j][k]-mul(tmp,A[i][k])+mod)%mod;
				B[j]=(B[j]-mul(tmp,B[i])+mod)%mod;
			}
	}
	for(i=1;i<n;i++)
		C[i]=mul(B[i],fpm(A[i][i],mod-2));
}
void dfs2(int x,int p)
{
	int i,j,v;  
	for(i=fir[x];i;i=e[i].nxt)
		if(e[i].to!=p)
		{
			v=e[i].to;
			if(fa[v]==x)
			{
				if(e[i].id<0)
					Ans[-e[i].id]=C[cro[v]];
				else
					Ans[e[i].id]=mod-C[cro[v]];
				dfs2(v,x);
			}		
			else if(dep[v]<dep[x])
			{
				int u=x; LL sum=0;
				while(u!=v)
				{
					sum=(sum+mul(C[cro[u]],cb[u]))%mod;
					u=fa[u];
				}
				sum=(d[x]-d[v]+e[i].A+sum+mod)%mod;
				sum=mul(sum,fpm(e[i].B,mod-2));
				if(e[i].id<0)
					Ans[-e[i].id]=mod-sum;
				else 
					Ans[e[i].id]=sum;
			}
		}
}
int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	int i,x,y; LL t1,t2;
	n=read(); m=read(); mod=read();
	for(i=1;i<=m;i++)
	{
		x=read(); y=read();
		t1=read(); t2=read();
		e[++cnt]=edge(x,y,t1,t2,i);
		e[++cnt]=edge(y,x,mod-t1,t2,-i);
	}
	dfs(1,0); 
	gauss(); 
	dfs2(1,0);
	for(i=1;i<=m;i++)
		printf("%lld\n",Ans[i]%mod);
	return 0;
}
