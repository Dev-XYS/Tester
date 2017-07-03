#include <bits/stdc++.h>
#define M 10010
#define int long long

using namespace std;

typedef long long ll;

ll mulslow(ll x, ll y, ll p)
{
	ll ans = 0;
	while(y) {
		if(y & 1) ans = (ans + x) % p;
		x = (x + x) % p, y >>= 1;
	}
	return ans;
}

ll mul(ll x, ll y, ll p)
{
	x = (x % p + p) % p, y = (y % p + p) % p;
	if(p <= 1e9) return x * y % p;
	if(p <= 1e12) return ((((x >> 20) * y % p) << 20) + (x & ((1 << 20) - 1)) * y) % p;
	ll tmp = floor((long double) x * y / p + 0.5);
	return ((x * y - tmp * p) % p + p) % p;
}

ll powmod(ll x, ll y, ll p)
{
	ll ans = 1;
	while(y) {
		if(y & 1) ans = mul(ans, x, p);
		x = mul(x, x, p), y >>= 1;
	}
	return ans;
}

ll Rev(ll x, ll p) {return powmod(x, p - 2, p);}

ll H[M], N[M], G[M], VA[M], VB[M], Vid[M], Mat[2222][111], Cnt = 1, n, m, Et = 0, cor[M], Etim = 0, FF[M], Ans[M], P;

struct edge {ll x, y, a, b, id; edge(){} edge(ll _1, ll _2, ll _3, ll _4, ll _5) {x = _1, y = _2, a = _3, b = _4, id = _5;}} E[M];

struct vec
{
	ll X[111];
	vec () {memset(X, 0, sizeof X);}
	vec operator - (const vec& A)
	{
		vec ans;
		for(int i = 1; i <= n; i++) ans.X[i] = (X[i] - A.X[i]) % P;
		return ans;
	}
	vec operator + (const vec& A)
	{
		vec ans;
		for(int i = 1; i <= n; i++) ans.X[i] = (X[i] + A.X[i]) % P;
		return ans;
	}
	vec operator * (const ll& A)
	{
		vec ans;
		for(int i = 1; i <= n; i++) ans.X[i] = mul(X[i], A, P);
		return ans;
	}
} MatV[222], Tmp[222], vecE[2222];

int getf(int x) {return FF[x] == x ? x : FF[x] = getf(FF[x]);}

void addedge(int x, int y, int a, int b, int c) {G[++Cnt] = y, N[Cnt] = H[x], H[x] = Cnt, VA[Cnt] = a, VB[Cnt] = b, Vid[Cnt] = c;}

void DFS1(int x, int f = -1)
{
	for(int T = H[x]; T; T = N[T]) if(G[T] != f) {
		cor[T] = ++Etim;
		MatV[x].X[cor[T]] = (MatV[G[T]].X[cor[T]] + 1) % P;
		MatV[G[T]].X[cor[T]] = (MatV[G[T]].X[cor[T]] - 1 + P) % P;
		Tmp[G[T]] = Tmp[x];
		Tmp[G[T]].X[cor[T]] = (Tmp[G[T]].X[cor[T]] + VB[T]) % P;
		Tmp[G[T]].X[n] = (Tmp[G[T]].X[n] + VA[T]) % P;
		DFS1(G[T], x);
	}
}

void getans(int x, int f = -1)
{
	for(int T = H[x]; T; T = N[T]) if(G[T] != f) Ans[abs(Vid[T])] = (Vid[T] < 0 ? -1 : 1) * MatV[cor[T]].X[n], getans(G[T], x);
}

void gauss()
{
	for(int i = 1; i < n; i++) {
		ll k = -1, tmp;
		for(int j = i; j <= n; j++) if(MatV[j].X[i]) {k = j, tmp = MatV[j].X[i]; break;}
		if(k > 0) swap(MatV[i], MatV[k]); else continue;
		ll rev = Rev(tmp, P);
		MatV[i] = MatV[i] * rev;
		for(int j = i + 1; j <= n; j++) MatV[j] = MatV[j] - MatV[i] * MatV[j].X[i];
	}
	assert(!(MatV[n].X[n] %= P));
	for(int i = n - 1; i >= 1; i--) {
		ll rev = Rev(MatV[i].X[i], P);
		MatV[i].X[i] = 1, MatV[i].X[n] = mul(MatV[i].X[n], rev, P);
		for(int j = 1; j < i; j++) MatV[j].X[n] = (MatV[j].X[n] - mul(MatV[i].X[n], MatV[j].X[i], P)) % P;
	}
}

#undef int
int main()
#define int long long
{
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &m, &P);
	for(int i = 1; i <= n; i++) FF[i] = i;
	for(int i = 1; i <= m; i++) {
		ll x, y, a, b;
		scanf("%lld%lld%lld%lld", &x, &y, &a, &b);
		if(getf(x) == getf(y)) E[++Et] = edge(x, y, a, b, i);
		else FF[getf(x)] = getf(y), addedge(x, y, a, b, i), addedge(y, x, P - a, b, -i);
	}
	memset(cor, -1, sizeof cor);
	DFS1(1);
	for(int i = 1; i <= Et; i++) {
		vec nw = Tmp[E[i].y] - Tmp[E[i].x]; //!!!
		nw.X[n] = (nw.X[n] - E[i].a) % P;
		ll rev = Rev(E[i].b, P);
		for(int j = 1; j <= n; j++) nw.X[j] = mul(nw.X[j], rev, P);
		MatV[E[i].x] = MatV[E[i].x] + nw;
		MatV[E[i].y] = MatV[E[i].y] - nw;
		vecE[i] = nw;
	}
	gauss();
	getans(1);
	for(int i = 1; i <= Et; i++) {
		Ans[E[i].id] = -vecE[i].X[n];
		for(int j = 1; j < n; j++) Ans[E[i].id] = (Ans[E[i].id] + mul(vecE[i].X[j], MatV[j].X[n], P)) % P;
	}
	for(int i = 1; i <= m; i++) printf("%lld\n", (Ans[i] % P + P) % P);
	return 0;
}
