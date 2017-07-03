#include <cstdio>
#include <cstring>

using namespace std;

int T, n, m, C, D, mod, ans;
bool wall[10][10], cover[10][10];

bool check()
{
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (wall[i][j] == true && cover[i][j] == true)
			{
				cnt++;
			}
		}
	}
	return cnt <= D;
}

void dfs2(int x, int y)
{
	if (x == n && y == m)
	{
		if (check() == true)
		{
			ans++;
		}
		return;
	}
	cover[x][y] = true;
	if (x < n && !cover[x + 1][y]) dfs2(x + 1, y);
	if (y < m && !cover[x][y + 1]) dfs2(x, y + 1);
	cover[x][y] = false;
}

void dfs1(int x, int y)
{
	if (x == n && y == m)
	{
		dfs2(1, 1);
		return;
	}
	cover[x][y] = true;
	if (x < n) dfs1(x + 1, y);
	if (y < m) dfs1(x, y + 1);
	cover[x][y] = false;
}

int main()
{
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d%d%d%d", &n, &m, &C, &D, &mod);
		memset(wall, 0, sizeof(wall));
		int x, y;
		for (int i = 0; i < C; i++)
		{
			scanf("%d%d", &x, &y);
			wall[x][y] = true;
		}
		ans = 0;
		dfs1(1, 1);
		printf("%d\n", ans / 2 % mod);
	}
	return 0;
}
