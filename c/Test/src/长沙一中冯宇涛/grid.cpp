#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 55
using namespace std;
inline int read(){
	int sum = 0, t = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ sum = sum * 10 + ch - '0'; ch = getchar(); }
	return sum * t;
}

int n, m, C, D, mod, phi;
int f[2][N][N][205];
bool mp[N][N];

int quick_mod(int x, int y){
	int res = 0; x %= mod;
	for(; y ; y >>= 1, x = 1LL * x * x % mod)
		if(y & 1) res = 1LL * res * x % mod;
	return res;
}

int get_phi(){
	phi = mod;
	int x = mod;
	for(int i = 2; i * i <= mod; i++) if(x % i == 0){
		phi = phi / i * (i - 1);
		while(x % i == 0) x /= i;
	}
	if(x) phi = phi / x * (x - 1);
}

void upd(int &x, int y){ x += y; if(x >= mod) x -= mod; }

int main(){
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	for(int T = read(); T ; T--){
		n = read(); m = read(); C = read(); D = read(); mod = read();
		get_phi();
		memset(mp, 0, sizeof(mp));
		for(int i = 1; i <= C; i++){
			int x = read(), y = read();
			mp[x][y] = true;
		}
		memset(f, 0, sizeof(f));
		int cur = 1, pre = 0;
		f[cur][1][1][0] = 1;
		for(int i = 2; i < n + m; i++){
			swap(cur, pre);
			memset(f[cur], 0, sizeof(f[cur]));
			for(int j = max(1, i - m); j <= n; j++)
			for(int k = i == 2 ? j : j + 1; k <= n; k++)
			for(int l = 0; l <= D; l++)
				for(int x1 = 0; x1 < 2; x1++)
				for(int x2 = 0; x2 < 2; x2++)
					upd(f[cur][j + x1][k + x2][l + mp[j + x1][i + 1 - j - x1] + mp[k + x2][i + 1 - k - x2]], f[pre][j][k][l]);
		}
		int ans = 0;
		for(int i = 0; i <= D; i++)
			upd(ans, f[cur][n][n][i]);
		printf("%d\n", ans);
	}
}



