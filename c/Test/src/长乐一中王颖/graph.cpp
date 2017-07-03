#include <cstdio>
typedef long long ll;
inline int Get() {
	char ch;
	while ((ch = getchar()) < '0' || ch > '9');
	int Num = ch - '0';
	while ((ch = getchar()) >= '0' && ch <= '9')
		Num = (Num << 3) + (Num << 1) + ch - '0';
	return Num;
}

inline ll Get64() {
	char ch;
	while ((ch = getchar()) < '0' || ch > '9');
	ll Num = ch - '0';
	while ((ch = getchar()) >= '0' && ch <= '9')
		Num = (Num << 3) + (Num << 1) + ch - '0';
	return Num;
}

const int N = 105;
const int M = 2e3 + 3;
int n, m, tot, first[N], next[M << 1], end[M << 1], vis[N], Case;
ll Mod, valA[M << 1], valB[M << 1], valC[M << 1], distA[N], distBC[N], distB[N];

inline ll mul(ll x, ll y) {
	x %= Mod; if (x < 0) x += Mod;
	y %= Mod; if (y < 0) y += Mod;
	ll res = 0, r = x;
	
	for (; y; y >>= 1) {
		if (y & 1) if ((res += r) >= Mod) res -= Mod;
		if ((r += r) >= Mod) r -= Mod;
	}
	return res;
}
inline ll pow(ll x, ll k) {
	x %= Mod; if(x < 0) x += Mod;
	ll res = 1, r = x;
	for (; k; k >>= 1, r = mul(r, r))
		if (k & 1) res = mul(res, r);
	return res;
}
inline void AddEdge(int x, int y, ll Ai, ll Bi, ll Ci) {
	next[++tot] = first[x], first[x] = tot, end[tot] = y, valA[tot] = Ai, valB[tot] = Bi, valC[tot] = Ci; 
	next[++tot] = first[y], first[y] = tot, end[tot] = x, valA[tot] = -Ai, valB[tot] = Bi, valC[tot] = -Ci;
}
void Dfs(int u) {
	for (int k = first[u], v; v = end[k], k; k = next[k])
		if (vis[v] != Case) {
			vis[v] = Case;
			if ((distA[v] = distA[u] + valA[k]) >= Mod) distA[v] -= Mod;
			if ((distB[v] = distB[u] + valB[k]) >= Mod) distB[v] -= Mod;
			if ((distBC[v] = distBC[u] + (ll)valB[k] * valC[k] % Mod) >= Mod) distBC[v] -= Mod; 
			Dfs(v);
		}
}
void Update(int u, int fa, ll res) {
	for (int k = first[u], v; v = end[k], k; k = next[k])
		if (v != fa) {
			if ((valC[k] += res) >= Mod) valC[k] -= Mod;
			if ((valC[k ^ 1] -= res) < 0) valC[k ^ 1] += Mod;
			if (vis[v] != Case) vis[v] = Case, Update(v, u, res);	
		}
}
inline ll QueryC(int x, int y, ll Ai, ll Bi) {
	++Case;
	vis[y] = Case, distA[y] = 0, distB[y] = 0, distBC[y] = 0, Dfs(y);
	if (vis[x] != Case) return 0; 
	
	ll res = mul(Ai + distA[x] - distBC[x],  pow(distB[x] + Bi, Mod - 2));
	if (res) {
		++Case; if (res < 0) res += Mod;
		Update(y, 0, res);
	}
	return res;
}
int main() {
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
	n = Get(), m = Get(), Mod = Get64(); tot = 1;
	for (int i = 1; i <= m; ++i) {
		int x = Get(), y = Get();
		ll A = Get64() % Mod, B = Get64() % Mod;
		AddEdge(x, y, A, B, QueryC(x, y, A, B));
	}
	for (int k = 2; k < tot; k += 2) printf("%lld\n", valC[k]);
	fclose(stdin);
	fclose(stdout);
}