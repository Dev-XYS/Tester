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
const int N=100005,M=N<<1;

int v[M],w[M],nxt[M];
int head[N],p[N],par[N],preve[N];
ll dis[N],dist[N];
bool kicked[M];
int n,m,s,ty,qry;

il void addedge(int p,int x,int y,int z){
	v[p]=y,w[p]=z;
	nxt[p]=head[x],head[x]=p;
}

il int suc(int i){ return i==N-1?0:i+1;}
il int pre(int i){ return i==0?N-1:i-1;}

il void upd(ll dist[N],int s){
	static bool used[N];
	static int q[N],st,ed;
	st=ed=0;
	q[ed=suc(ed)]=s,used[s]=true;
	memset(used+1,0,sizeof(bool)*n);
	while(st!=ed){
		int u=q[st=suc(st)];
		used[u]=false;
		for(int e=head[u];e;e=nxt[e]){
			if(kicked[e>>1]||dist[v[e]]<=dist[u]+w[e]) continue;
			dist[v[e]]=dist[u]+w[e];
			if(!used[v[e]]){
				used[v[e]]=true;
				if(dist[q[st+1]]>dist[v[e]]){
					q[st]=v[e];
					st=pre(st);
				}else{
					ed=suc(ed);
					q[ed]=v[e];
				}
			}
		}
	}
}

il void getpar(){
	static bool used[N];
	int u=s,rest=n-1;
	used[s]=true;
	while(rest){
		int cur=0;
		for(int e=head[u];e;e=nxt[e]){
			if(used[v[e]]||dis[u]+w[e]!=dis[v[e]]) continue;
			if(!cur||p[v[e]]<p[cur]) cur=v[e];
		}
		if(!cur){
			u=par[u];
		}else{
			--rest,used[cur]=true;
			par[cur]=u,u=cur;
		} 
	}
	
}

int main(){
	fileio("road");
	scanf("%d%d%d%d",&n,&m,&s,&ty);
	rep(i,1,n) scanf("%d",p+i);
	rep(i,1,m){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		addedge(lch(i),x,y,z);
		addedge(rch(i),y,x,z); 
	} 
	fill(dis+1,dis+n+1,linf),dis[s]=0;
	upd(dis,s);
	getpar();
//	rep(i,1,n) cerr<<i<<":"<<dis[i]<<" "<<par[i]<<endl;
	rep(i,1,m){
		int x=v[rch(i)],y=v[lch(i)];
		if(par[y]==x) preve[y]=i;
		if(par[x]==y) preve[x]=i;
	}
	scanf("%d",&qry);
	int ans=0;
	while(qry--){
		int x,y; 
		scanf("%d%d",&x,&y);
		if(ty) x^=ans,y^=ans;
		ans=0;
		for(int u=y;u!=x;u=par[u]) kicked[preve[u]]=true,++ans;
		fill(dist+1,dist+n+1,linf),dist[s]=0;
		upd(dist,s);
		int u=y;
		while(dist[y]!=dis[y]){
			--ans;
			kicked[preve[u]]=false;
			if(dist[u]<dist[par[u]]) upd(dist,u);
			else if(dist[par[u]]<dist[u]) upd(dist,par[u]);
			u=par[u];
		}
		while(u!=x) kicked[preve[u]]=false,u=par[u];
		printf("%d\n",ans);
	}
	return 0;
}

