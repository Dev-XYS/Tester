#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 205
#define M 2005
using namespace std;
typedef long long ll;
inline ll read(){
	ll sum = 0, t = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ sum = sum * 10 + ch - '0'; ch = getchar(); }
	return sum * t;
}

int n, m;
ll mod;

void upd(ll &x, ll y){ x += y; if(x >= mod) x -= mod; }

ll mul(ll x, ll y){
	ll res = 0; x %= mod;
	for(; y ; y >>= 1, upd(x, x))
		if(y & 1) upd(res, x);
	return res;
}

ll quick_mod(ll x, ll y){
	ll res = 1; x %= mod;
	for(; y ; y >>= 1, x = mul(x, x))
		if(y & 1) res = mul(res, x);
	return res;
}

int r;
ll A[N][N], B[N];

void gauss(){
	for(int i = 1; i <= r; i++){
		for(int j = i; j <= r; j++) if(A[j][i]){ swap(A[i], A[j]); swap(B[i], B[j]); break ; }
		ll tmp = quick_mod(A[i][i], mod - 2);
		for(int j = 1; j <= r; j++) if(A[j][i] && j != i){
			ll ret = mul(A[j][i], tmp);
			for(int k = 1; k <= r; k++)
				upd(A[j][k], mod - mul(A[i][k], ret));
			upd(B[j], mod - mul(B[i], ret));
		}
	}
}

int mp[N][N], fa[N];
int tot, num;
int u[M], v[M], up[N], lst[N], at_up[N], at_lst[N];
int nxt[M<<1], fir[N], to[M<<1], cnt;
ll wa[M<<1], wb[M<<1];
ll upa[N], upb[N], fucka[M], fuckb[M];
vector<int>cir[M];
bool ban[M], vis[N];

void add(int x, int y, ll a, ll b){
	nxt[++cnt] = fir[x]; to[cnt] = y; fir[x] = cnt; wa[cnt] = a; wb[cnt] = b;
	nxt[++cnt] = fir[y]; to[cnt] = x; fir[y] = cnt; wa[cnt] = mod - a; wb[cnt] = b;
}

int st[N], top;

void dfs(int x){
	vis[x] = true;
	st[++top] = x;
	for(int i = fir[x]; i ; i = nxt[i]) if(!ban[i]){
		int y = to[i];
		ban[((i + 1) ^ 1) - 1]= true;
		if(vis[y]){
			ll k = A[at_lst[y]][lst[y]];
			for(int j = 1; j <= tot; j++)
				A[at_lst[y]][j] = mul(A[at_lst[y]][j], wb[i]);
			B[at_lst[y]] = mul(B[at_lst[y]], wb[i]);
			++num;
			for(int j = top; st[j] != y ; j--){
				upd(A[at_lst[y]][up[st[j]]], mul(k, upb[st[j]]));
				upd(B[at_lst[y]], mul(k, upa[st[j]]));
				cir[num].push_back(st[j]);
			}
			cir[num].push_back(y);
			fucka[num] = wa[i];
			fuckb[num] = wb[i];
			upd(B[at_lst[y]], mul(wa[i], k));
			
			k = A[at_lst[x]][lst[x]];
			for(int j = 1; j <= tot; j++)
				A[at_lst[x]][j] = mul(A[at_lst[x]][j], wb[i]);
			B[at_lst[x]] = mul(B[at_lst[x]], wb[i]);
			for(int j = top; st[j] != y ; j--){
				upd(A[at_lst[x]][up[st[j]]], mul(k, mod - upb[st[j]]));
				upd(B[at_lst[x]], mul(k, mod - upa[st[j]]));
			}
			upd(B[at_lst[x]], mul(mod - wa[i], k));
			
		}
		else {
			fa[y] = x;
			A[at_up[x]][up[y]] = 1;
			upa[y] = wa[i];
			upb[y] = wb[i];
			dfs(y);
		}
	}
	top--;
}

int main(){
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
	n = read(); m = read(); mod = read();
	for(int i = 1; i <= n; i++) up[i] = ++tot, lst[i] = ++tot;
	for(int i = 1; i <= n; i++)
		A[at_lst[i] = ++r][lst[i]] = 1, A[at_up[i] = ++r][up[i]] = mod - 1, A[at_up[i]][lst[i]] = mod - 1;
	for(int i = 1; i <= m; i++){
		u[i] = read(); v[i] = read();
		ll a = read(), b = read();
		add(u[i], v[i], a, b);
	}
	dfs(1);
	gauss();
	for(int i = 1; i <= n; i++){
		up[i] = mul(B[up[i]], quick_mod(A[up[i]][up[i]], mod - 2));
		mp[fa[i]][i] = up[i];
		mp[i][fa[i]] = mod - up[i];
	}
	for(int i = 1; i <= num; i++){
		int x = cir[i][0], y = cir[i][cir[i].size() - 1];
		ll SA = 0;
		for(int j = 0; j < cir[i].size() - 1; j++)
			upd(SA, upa[cir[i][j]]), upd(SA, mod - mul(upb[cir[i][j]], up[cir[i][j]]));
		upd(SA, fucka[i]);
		mp[x][y] = mul(SA, quick_mod(fuckb[i], mod - 2));
		mp[y][x] = mod - mp[x][y];
	}
	for(int i = 1; i <= m; i++)
		printf("%lld\n", mp[u[i]][v[i]] % mod);
}
