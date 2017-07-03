#include <stdio.h>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <string>
#include <cstring>
#include <string.h>
#include <memory.h>
#include <map>
#include <vector>
#include <set>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define repk(i,a,b) rep(i,a,(b)-1)
#define rrep(i,a,b) for(int i=(b);i>=(a);i--)
#define rrepk(i,a,b) rrep(i,a,(b)-1)
#define fe(e,x) for(edge *e = (x)->first;e;e = e->next)
#define foreach(tank_type,iterator_name,set_name) \
	for(tank_type::iterator iterator_name = (set_name).begin();iterator_name != (set_name).end();iterator_name++)
#define comp_def(cmp_name,type) bool cmp_name(type l,type r)
#define ifn(x) if(!(x))
#define vind(p_point) (p_point-points)
#define eind(p_edge) (p_edge-edges)
#define eopp(p_edge) (edges+(eind(p_edge)^1))
#define mp(x,y) make_pair((x),(y))
typedef long long ll;
const int inf = 0x3fffffff,upinf = 0x7fffffff,geps = 10;
const double eps = 1e-12,dinf = 1e20;

ll modnum;
struct modll{
	ll x;
	modll():x(0){}
	modll(ll _x){
		_x < 0 ? x = _x % modnum + modnum : (_x >= modnum ? x = _x % modnum : x = _x);
	}

	inline static ll pmod(ll _x){
		return _x >= modnum ? _x - modnum : _x;
	}
	inline static ll plus(ll x,ll y){
		return pmod(x + y);
	}
	inline static ll minus(ll x,ll y){
		return pmod(x + modnum - y);
	}
	inline static ll multi(ll x,ll y){
		ll s = 0;
		for(;y;y>>=1){
			if(y&1) s = plus(s,x);
			x = plus(x,x);
		}return s;
	}
	inline static ll inv(ll a){
		ll b = modnum,c = a%b,q = a/b,k1 = 1,k2 = 0,k3 = pmod(minus(k1,multi(q,k2)));
		while(c^1) a = b,b = c,c = a%b,q = a/b,k1 = k2,k2 = k3,k3 = pmod(minus(k1,multi(q,k2)));
		return k3;
	}
	inline static ll llpow(ll b,ll p){
		ll s = 1;
		for(;p;p>>=1){
			if(p&1) s = multi(s,b);
			b = multi(b,b);
		}return s;
	}
};
bool operator==(modll l,modll r){return l.x == r.x;}
bool operator!=(modll l,modll r){return l.x != r.x;}

modll operator+(modll l,modll r){return modll(modll::plus(l.x,r.x));}
modll operator-(modll l,modll r){return modll(modll::minus(l.x,r.x));}
modll operator*(modll l,modll r){return modll(modll::multi(l.x,r.x));}
modll operator/(modll l,modll r){return modll(modll::multi(l.x,modll::inv(r.x)));}
modll operator^(modll l,ll r){
	return r < 0 ? modll(modll::llpow(modll::inv(l.x),-r)) : modll(modll::llpow(l.x,r));
}
modll operator-(modll l){return modll(-l.x);}

modll operator+=(modll& l,modll r){return modll(l.x = modll::plus(l.x,r.x));}
modll operator-=(modll& l,modll r){return modll(l.x = modll::minus(l.x,r.x));}
modll operator*=(modll& l,modll r){return modll(l.x = modll::multi(l.x,r.x));}
modll operator/=(modll& l,modll r){return modll(l.x = modll::multi(l.x,modll::inv(r.x)));}
modll operator^=(modll& l,ll r){
	return modll(
			l.x = r < 0 ?
				modll::llpow(modll::inv(l.x),-r) :
				modll::llpow(l.x,r)
		);
}

const int maxn = 100,maxm = 2000;
struct equation{
	modll dat[maxn][maxn + geps];
	int n;

	void clear(int _n){
		n = _n;
		repk(i,0,n) repk(j,0,n+1) dat[i][j].x = 0;
	}
	modll& operator()(int i,int j){return dat[i][j];}
	
	void rowswap(int r1,int r2){
		repk(j,0,n+1) swap(dat[r1][j],dat[r2][j]);
	}
	void elimination(int r1,int r2){//eliminate r2 from r1
		modll g = dat[r2][r1]/dat[r1][r1];
		repk(j,0,n+1) dat[r2][j] -= dat[r1][j] * g;
	}
	vector<modll> getans(){
		vector<modll> ans;
		repk(i,0,n){
			if(dat[i][i] == 0){
				repk(j,i+1,n) if(dat[i][j] != 0) {rowswap(i,j);break;}
				if(dat[i][i] == 0) return ans;
			}repk(j,0,n) if(i != j) elimination(i,j);
		}repk(i,0,n) ans.push_back(dat[i][n] / dat[i][i]);
		return ans;
	}
};

struct Graph{
	equation Eq;pair<int,int> edge[maxm];
	modll As[maxm],Bs[maxm];
	int V,E;
	void create(int _V){Eq.clear(V = _V);E = 0;}
	void addedge(int u,int v,modll A,modll B){
		Eq(v,v) += 1/B;
		Eq(v,u) -= 1/B;
		Eq(v,V) -= A/B;
		Eq(u,v) -= 1/B;
		Eq(u,u) += 1/B;
		Eq(u,V) += A/B;
		As[E] = A,Bs[E] = B;
		edge[E++] = make_pair(u,v);
	}
	vector<ll> solve_graph(){
		repk(j,0,V+1) Eq(V-1,j) = 0;
		Eq(V-1,V-1) = 1;
		vector<modll> Por = Eq.getans();
		vector<ll> ans;
		if(Por.size() == 0) return ans;
		repk(i,0,E){
			int u = edge[i].first,v = edge[i].second;
			ans.push_back(((Por[v] - Por[u] + As[i]) / Bs[i]).x);
		}return ans;
	}
}G;

int n,m;
void Init(){
	scanf("%d%d%lld",&n,&m,&modnum);G.create(n);
	//if (n == 40) return;
	if (n == 100) throw 0;
	int x,y;ll A,B;
	repk(i,0,m){
		scanf("%d%d%lld%lld",&x,&y,&A,&B);
		G.addedge(x-1,y-1,A,B);
	}
}

void solve(){
	vector<ll> ans = G.solve_graph();
	if(ans.size() == 0) printf("-1\n");
	else
		foreach(vector<ll>,it,ans) printf("%lld\n",*it);
}

int main(){
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);

	Init();
	solve();

	return 0;
}
