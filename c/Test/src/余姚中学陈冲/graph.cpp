#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int LEN = 2005;
int i, j, k, n, m, s, t, cnt, top, S;
ll a[LEN][LEN], b[LEN][LEN];
int id[LEN][LEN], stk[LEN];
bool flag[LEN];
ll ans[LEN], mod;
void Plus(ll &x, ll y) {
	x += y;
	if (x >= mod) {
		x -= mod;
	}
}
ll mul(ll x, ll y) {
	if (y == 0) {
		return 0;
	}
	ll ans = mul(x, y >> 1);
	Plus(ans, ans);
	if (y & 1) {
		Plus(ans, x);
	}
	return ans;
}
ll pow_mod(ll x, ll y) {
	if (y == 0) {
		return 1;
	}
	ll ans = pow_mod(x, y >> 1);
	if (y & 1) {
		return mul(mul(ans, ans), x);
	} else {
		return mul(ans, ans);
	}
}
struct Gauss {
	ll t[10005][205];
	int n, m;
	void init(int k) {
		n = k;
		m = 0;
	}
	void add_node(int u) {
		m++;
		for (int v = 1; v <= n; v++) {
			if (id[u][v]) {
				if (id[u][v] > 0) {
				    t[m][id[u][v]] = 1;
				} else {
					t[m][-id[u][v]] = mod - 1;
				}
			}
		}
	}
	void add_ring() {
		m++;
		for (int i = 1; i < top; i++) {
			int u = stk[i], v = stk[i + 1];
			Plus(t[m][n + 1], a[u][v]);
			if (id[u][v] > 0) {
				t[m][id[u][v]] = b[u][v];
			} else {
				t[m][-id[u][v]] = mod - b[u][v];
			}
		}
	}
	void DO() {
		for (int i = 1; i <= n; i++) {
			int j = i;
			for (; j <= m; j++) {
				if (t[j][i]) {
					if (j != i) {
						for (int k = 1; k <= n + 1; k++) {
							swap(t[j][k], t[i][k]);
						}
					}
					break;
				}
			}
			ll inv = pow_mod(t[i][i], mod - 2);
			for (int j = i + 1; j <= m; j++) {
				ll tmp = mul(t[j][i], inv);
				for (int k = 1; k <= n + 1; k++) {
					t[j][k] -= mul(t[i][k], tmp);
					if (t[j][k] < 0) {
						t[j][k] += mod;
					}
				}
			}
		}
		for (int i = n; i >= 1; i--) {
			ans[i] = mul(t[i][n + 1], pow_mod(t[i][i], mod - 2));
			for (int j = 1; j < i; j++) {
				if (t[j][i]) {
					t[j][n + 1] -= mul(ans[i], t[j][i]);
					if (t[j][n + 1] < 0) {
						t[j][n + 1] += mod;
					}
					t[j][i] = 0;
				}
			}
		}
	}
} gauss;
void dfs(int u) {
	stk[++top] = u;
	flag[u] = true;
	if (top >= 3 && id[u][S]) {
		stk[++top] = S;
		gauss.add_ring();
		top--;
	}
	for (int v = S + 1; v <= n; v++) {
		if (id[u][v] && flag[v] == false) {
			dfs(v);
		}
	}
	top--;
	flag[u] = false;
}
int main() {
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
	scanf("%d %d %lld", &n, &m, &mod);
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		scanf("%lld %lld", &a[x][y], &b[x][y]);
		a[y][x] = mod - a[x][y];
		b[y][x] = b[x][y];
		id[x][y] = ++cnt;
		id[y][x] = -cnt;
	}
	gauss.init(m);
	for (S = 1; S <= n; S++) {
		dfs(S);
	}
	for (int i = 1; i <= n; i++) {
		gauss.add_node(i);
	}
	gauss.DO();
	for (int i = 1; i <= m; i++) {
		printf("%lld\n", ans[i]);
	}
	return 0;
}
