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
const int N=100005;
const int go[2][2]={{0,1},{1,0}};

int n,m,c,d,mod;
pii pos[205]; 

il void inc(int &x,const int &y){
	x+=y;
	if(x>=mod) x-=mod;
}

namespace task1{
	const int N=53;
	bool g[N][N];
	int f[N<<1][N][N][N];
	
	il bool in(int x,int y){
		return x>0&&x<n+1&&y>0&&y<m+1;
	}
	
	il void solve(){
		memset(g,0,sizeof(g));
		rep(i,1,c) g[pos[i].X][pos[i].Y]=true;
		memset(f,0,sizeof(f));
		f[1][0][1][1]=1;
		rep(step,1,n+m-2) rep(k,0,d){
			rep(i1,1,n){
				int j1=step+1-i1;
				if(!in(i1,j1)) continue;
				rep(i2,i1,n){
					int j2=step+1-i2;
					if(!in(i2,j2)||i1==i2&&step!=1) continue;
					int &cur=f[step][k][i1][i2];
					if(!cur) continue;
				//	cerr<<step<<" "<<k<<" "<<i1<<" "<<i2<<":"<<cur<<endl;
					rep0(c1,2){
						int ni1=i1+go[c1][0],nj1=j1+go[c1][1];
						if(!in(ni1,nj1)) continue;
						rep0(c2,2){
							int ni2=i2+go[c2][0],nj2=j2+go[c2][1];
							if(!in(ni2,nj2)||ni2<ni1) continue;
						//	cerr<<ni1<<","<<nj1<<" "<<ni2<<","<<nj2<<endl;
							inc(f[step+1][k+g[ni1][nj1]+g[ni2][nj2]][ni1][ni2],cur);
						}
					}
				}
			}
		}
		int ans=0;
		rep(i,0,d) inc(ans,f[n+m-1][i][n][n]);
		printf("%d\n",ans);
	}
}

int main(){
	fileio("grid");
	int kase;
	scanf("%d",&kase);
	while(kase--){
		scanf("%d%d%d%d%d",&n,&m,&c,&d,&mod);
		rep(i,1,c) scanf("%d%d",&pos[i].X,&pos[i].Y);
		if(n<=50&&m<=50) task1::solve();
	}
	return 0;
}
/*
4
2 3 0 0 10
2 3 1 0 16
2 1
3 3 1 0 7
2 2
2 2 2 1 11
1 2
2 1
*/
