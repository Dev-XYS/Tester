#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 1005;
int c, d, mod;
bool a[10][10], b[10][10];
int n, m, i, j, k, dx[2] = {0, 1}, dy[2] = {1, 0}, ans;
inline void dfs(int x, int y, int xx, int yy, int tt)
{
	if (tt > d) return;
	if (x == n && y == m && xx == n && yy == m) {ans ++; return;}
	if (x == xx && y == yy && x != 1 && y != 1) return;
	for(int i = 0; i < 2; i ++)
		for(int j = 0; j < 2; j ++)
		{
			int nx = dx[i] + x, ny = dy[i] + y, nxx = xx + dx[j], nyy = yy + dy[j];
			if (nx <= n && ny <= m && nxx <= n && nyy <= m)
			{
				if (nx == nxx && nx == n && ny == nyy && ny == m)
				{
					dfs(nx, ny, nxx, nyy, tt);
				}
				else if (!(nx == nxx && ny == nyy) && !a[nx][ny] && !a[nxx][nyy])
				{
					a[nx][ny] = a[nxx][nyy] = 1;
					dfs(nx, ny, nxx, nyy, tt + b[nx][ny] + b[nxx][nyy]);
					a[nx][ny] = a[nxx][nyy] = 0;
				}
			}
		}
}
int main()
{
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	int T; cin >> T;
	while (T--)
	{
		cin >> n >> m >> c >> d >> mod;
		memset(b, 0, sizeof(b));
		ans = 0;
		for(i = 1; i <= c; i ++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			b[x][y] = 1;
		}
		dfs(1, 1, 1, 1, 0);
		cout << ans/2 << endl;
	}
}