#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<cstdio>
#include<cctype>
#include<cassert>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<cstring>
#include<string>
#include<queue>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<stack>
#include<iomanip>
#include<utility>
using namespace std;
#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define rg register
#define il inline
#define lch(x) ((x)<<1)
#define rch(x) ((x)<<1^1)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define rep0(i,n) for(register int i=0;i<(n);++i)
#define rep(i,st,ed) for(register int i=(st);i<=(ed);++i)
#define per(i,ed,st) for(register int i=(ed);i>=(st);--i)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double dbl;
typedef long double ldb;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
template<typename T> il T qmin(const T &a,const T &b){return a<b?a:b;}
template<typename T> il T qmax(const T &a,const T &b){return a>b?a:b;}
template<typename T> il void getmin(T &a,const T &b){if(a>b) a=b;}
template<typename T> il void getmax(T &a,const T &b){if(a<b) a=b;}
il void fileio(string s){
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}

const int inf=(int)1e9+7;
const ll linf=(ll)1e17+7;
const int N=205,M=2005;

int v[M<<1],nxt[M<<1];
ll a[M],b[M];
int head[N],n,m;
ll mod,g[N+M][M];
bool used[M];
int cnt;

il void addedge(int p,int x,int y){
	v[p]=y,nxt[p]=head[x],head[x]=p;
}

il void inc(ll &x,const ll &y){
	x+=y;
	if(x>=mod) x-=mod;
}

il void dec(ll &x,const ll &y){
	x-=y;
	if(x<0) x+=mod;
}

il ll mul(ll x,ll y){
	ll ans=0;
	while(y){
		if(y&1) inc(ans,x);
		inc(x,x);
		y>>=1;
	}
	return ans;
}

il ll qpow(ll x,ll y){
	ll ans=1;
	while(y){
		if(y&1) ans=mul(ans,x);
		x=mul(x,x);
		y>>=1;
	}
	return ans;
}

il void gauss(ll a[N+M][M],int n,int m){
	rep(v,1,m){
		int cur=0;
		rep(i,v,n)if(a[i][v]){
			cur=i;
			break;
		}
		assert(cur!=0);
		if(cur!=v) rep(j,1,m+1) swap(a[v][j],a[cur][j]);
		int r=qpow(a[v][v],mod-2);
		rep(j,1,m+1) if(a[v][j]) a[v][j]=mul(a[v][j],r);
		rep(i,1,n)if(i!=v&&a[i][v]){
			per(j,m+1,v) dec(a[i][j],mul(a[v][j],a[i][v]));
		}
	/*	cerr<<"--after "<<v<<"---"<<endl;
		rep(i,1,cnt){
			rep(j,1,m+1) cerr<<a[i][j]<<" ";
			cerr<<endl;
		}
	*/
	}
}

int main(){
	fileio("graph");
	scanf("%d%d%lld",&n,&m,&mod);
	rep(i,1,m){
		int x,y;
		scanf("%d%d%lld%lld",&x,&y,a+i,b+i);
		addedge(lch(i),x,y);
		addedge(rch(i),y,x);
	}
	rep(u,1,n){
		++cnt;
		for(int e=head[u];e;e=nxt[e]){
			g[cnt][e>>1]=(e&1?mod-1:1);
		}
		g[cnt][m+1]=0;
	}
	rep(i,1,m)if(!used[i]){
		++cnt;
		static int q[N],preve[N],st,ed;
		static bool used[N];
		int x=v[lch(i)],y=v[rch(i)];
		memset(used+1,false,sizeof(bool)*n);
		st=0,ed=1,q[ed]=x,used[x]=true;
		while(st!=ed){
			int u=q[++st];
			for(int e=head[u];e;e=nxt[e]){
				if(used[v[e]]||(e>>1)==i) continue;
				used[v[e]]=true;
				q[++ed]=v[e];
				preve[v[e]]=e;
				if(v[e]==y) break;
			}
			if(used[y]) break;
		}
		if(!used[y]) continue;
		ll sum=a[i];
		for(int u=y,e=preve[u];u!=x;u=v[e^1],e=preve[u]){
			::used[e>>1]=true;
			if(e&1) g[cnt][e>>1]=mod-b[e>>1],dec(sum,a[e>>1]);
			else g[cnt][e>>1]=b[e>>1],inc(sum,a[e>>1]);
		}
		used[i]=true;
		g[cnt][i]=b[i];
		g[cnt][m+1]=sum;
	}
	assert(cnt>=m);
	gauss(g,cnt,m);
	rep(i,1,m) printf("%lld\n",g[i][m+1]);
	return 0;
}

