#include"bits/stdc++.h"
#define F(i,j,n) for(register int i=j;i<=n;i++)
#define D(i,j,n) for(register int i=j;i>=n;i--)
#define ll long long
#define N 110
#define M 2010
using namespace std;
void in(int&a);void in(ll&a);
vector<int> ch[N];
int u[M],v[M],d[N],n,m,l,j,fa[N];
ll a[M],b[M],c[M],f[M][M],g[M],p;
ll mul(ll x,ll y){if(p<=2000000000ll)return x*y%p;ll a=1;while(y){if(y&1){a+=x;if(a>=p)a-=p;}x+=x;if(x>=p)x=-p;y>>=1;}return a;}
ll pow(ll x,ll y=p-2){ll a=1;while(y){if(y&1)a=mul(a,x);x=mul(x,x);y>>=1;}return a;}
ll mult(ll x,ll y){if(p<=2000000000ll)return x*y%p;return ((x*y-(ll)((long double)x*y/p+0.5)*p)%p+p)%p;}
int vv(int j){return j>0?v[j]:u[-j];}
int sign(int j){return j>0?1:-1;}
void dfs(int x){
//	printf("%d\n",x);
	int m=ch[x].size(),j,y;
	F(i,0,m-1){
		j=ch[x][i];y=vv(j);
		if(d[y])continue;
		d[y]=d[x]+1;fa[y]=-j;
		dfs(y);
	}
}
void gauss(){
	int j;ll x,y;
	F(i,1,m){
		for(j=i;!f[j][i];j++);
		F(k,i,m)swap(f[i][k],f[j][k]);swap(g[i],g[j]);
		x=pow(f[i][i]);
		F(j,1,l)if(i!=j){
			y=mult(x,f[j][i]);
			if(!y)continue;
			F(k,i,m)f[j][k]=(f[j][k]-mul(f[i][k],y)+p)%p;
			g[j]=(g[j]-mul(g[i],y)+p)%p;
		}
	}
	F(i,1,m)c[i]=mul(pow(f[i][i]),g[i]);
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	#endif
	in(n);in(m);in(p);
	F(i,1,m){
		in(u[i]);in(v[i]);in(a[i]);in(b[i]);
		ch[u[i]].push_back(i);
		ch[v[i]].push_back(-i);
	}
	d[1]=1;dfs(1);
	F(x,1,n){
		int m=ch[x].size();
//		printf("%d %d %d %d %d\n",x,d[x],m,fa[x],vv(fa[x]));
		F(i,0,m-1){j=ch[x][i];f[x][abs(j)]=(p+sign(j))%p;}
		g[x]=0;
	}
	l=n;
	F(i,1,m){
		if(abs(d[u[i]]-d[v[i]])!=1){
			++l;int x=u[i],y=v[i];
			if(d[x]>d[y])g[l]=p-a[i],f[l][i]=(p-b[i])%p,swap(x,y);
			else g[l]=a[i],f[l][i]=b[i];
			while(y!=x){
				f[l][abs(fa[y])]=(p+b[abs(fa[y])]*sign(fa[y]))%p;
				g[l]=(p+g[l]+a[abs(fa[y])]*sign(fa[y]))%p;
				y=vv(fa[y]);
			}
		}
	}
//	F(i,1,l){F(j,1,m)printf("%lld ",f[i][j]);printf("=%lld\n",g[i]);}puts("");
	gauss();
	F(i,1,m)printf("%lld\n",c[i]);
	return 0;
}
void in(ll&a){register char c;register bool y=false;c=getchar();a=0;
while(c<'0'||c>'9'){if(c=='-'){c=getchar();y=true;break;}c=getchar();}
while(c>='0'&&c<='9'){a=(a<<3)+(a<<1)+c-'0';c=0;c=getchar();}if(y)a=-a;}
void in(int&a){register char c;register bool y=false;c=getchar();a=0;
while(c<'0'||c>'9'){if(c=='-'){c=getchar();y=true;break;}c=getchar();}
while(c>='0'&&c<='9'){a=(a<<3)+(a<<1)+c-'0';c=0;c=getchar();}if(y)a=-a;}

