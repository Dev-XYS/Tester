#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 105;
int a[MAXN][MAXN], b[MAXN][MAXN], c[MAXN][MAXN];
int mod;
int n, m, i, j, k, x[2005], y[2005];
inline int ksm(int x, int y, int z)
{
	int b = 1;
	while (y)
	{
		if (y & 1) b = b * (long long)x % z;
		x = x * (long long)x % z;
		y >>= 1;
	}
	return b;
}
int main()
{
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
	cin >> n >> m >> mod;
	for(i = 1; i <= m; i ++)
	{
		scanf("%d%d", &x[i], &y[i]);
		scanf("%d%d", &a[x[i]][y[i]], &b[x[i]][y[i]]);
		a[y[i]][x[i]] = -a[x[i]][y[i]];
		b[y[i]][x[i]] = b[x[i]][y[i]];
	}
	c[1][2] = c[2][3] = c[3][1] = (a[1][2] + a[2][3] + a[3][1]) * ksm(b[1][2] + b[2][3] + b[3][1], mod - 2, mod) % mod;
	c[2][1] = -c[1][2]; c[1][3] = -c[3][1]; c[3][2] = -c[2][3];
	for(i = 1; i <= m; i ++)
		printf("%d\n", (c[x[i]][y[i]] + mod) % mod);
}