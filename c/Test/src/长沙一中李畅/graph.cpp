#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define LL long long

const int Maxn = 105,Maxm = 2005;

inline LL read(){
	LL x = 0,f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch <= '9' && ch >= '0') 
		x = x*10+ch-'0',ch = getchar();
	return x*f;
}

struct Edge{
	int x , y; LL a , b;
}G[Maxm];

LL A[Maxm][Maxm],B[Maxm];
LL MOD;
int mp[Maxn][Maxn],fa[Maxn];
int hed[Maxn],to[Maxm<<1];
int dfn[Maxn],nxt[Maxm<<1];
int N , M , tot , idx , cnt;

inline LL upd(LL &x,LL y){
	x += y;
	if(x >= MOD) x -= MOD;
}

inline LL Mul(LL x,LL y){
	if(MOD <= 1000000000 || !x) return x * y % MOD;
	LL ret = 0;
	for( ; y ; y >>= 1,upd(x,x))
		if(y & 1) upd(ret , x);
	return ret;
}

inline LL fpm(LL x,LL y){
	LL ret = 1;
	for(  ; y ; y >>= 1,x = Mul(x,x))
		if(y & 1) ret = Mul(ret , x);
	return ret;
}

void Addedge(int x,int y){
	nxt[++cnt] = hed[x]; to[cnt] = y; hed[x] = cnt;
	nxt[++cnt] = hed[y]; to[cnt] = x; hed[y] = cnt;
}

void Add(int x,int y,int sgn){
	upd(A[x][y],sgn > 0 ? G[y].b : MOD - G[y].b);
	upd(B[x] , sgn > 0 ? G[y].a : MOD - G[y].a);
}

void dfs(int x,int p){
	dfn[x] = ++idx; fa[x] = p;
	for(int i = hed[x],v ; i ; i = nxt[i])
		if(!dfn[v = to[i]]) dfs(v,x);
		else if(dfn[v] > dfn[x] && v != p){
			int y = v,p; ++tot;
			while(y != x){
				p = fa[y];
				if(mp[y][p] < 0) Add(tot,-mp[y][p],-1);
				else Add(tot,mp[y][p],1);
				y = p;
			}
			if(mp[x][v] < 0) Add(tot,-mp[x][v],-1);
			else Add(tot,mp[x][v],1);
		}
}

void Gauss(){
	int i , j , k, n = M;  LL tmp;
	for(i = 1 ; i <= n ; ++i){
		for(j = i ; j <= n ; ++j) if(A[j][i]) break;
		if(j != i) swap(A[j] , A[i]) ,swap(B[j],B[i]);
		tmp = fpm(A[i][i],MOD-2); 
		for(j = i ; j <= n ; ++j) A[i][j] = Mul(A[i][j],tmp);
		B[i] = Mul(B[i] , tmp);
		for(j = i + 1 ; j <= n ; ++j) if(A[j][i]){
			for(k = i + 1 ; k <= n ; ++k)
				upd(A[j][k],MOD-Mul(A[j][i],A[i][k]));
			upd(B[j] , MOD-Mul(A[j][i],B[i]));
			upd(A[j][i],MOD-Mul(A[j][i],A[i][i]));
		}
	}

	for(i = n ; i ; --i)
		for(j = 1 ; j < i ; ++j) if(A[j][i])
			upd(B[j] , MOD - Mul(A[j][i],B[i]));
}

int main(){
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);

	N = read(); M = read(); MOD = read();
	for(int i = 1 ; i <= M ; ++i){
		G[i].x = read(); G[i].y = read();
		G[i].a = read(); G[i].b = read();
		++A[G[i].x][i]; upd(A[G[i].y][i],MOD-1);
		mp[G[i].x][G[i].y] = i;
		mp[G[i].y][G[i].x] = -i;
		Addedge(G[i].x , G[i].y);
	}

	tot = N - 1; 
	memset(A[N] , 0 , sizeof(A[N]));
	dfs(1,0); Gauss();
	for(int i = 1 ; i <= M ; ++i)
		printf("%lld\n",B[i]);
	return 0;
}
