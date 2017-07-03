#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, m, C, D, p;

struct node
{
	int x1, y1, x2, y2, s;
	node(){}
	node(int _x1, int _y1, int _x2, int _y2, int _s) { x1 = _x1, y1 = _y1, x2 = _x2, y2 = _y2, s = _s; }
};
queue < node > que;
int Map[60][60];
int f[21][21][21][21][51];
bool bo[21][21][21][21][51];
int dx[2] = {0, 1};
int dy[2] = {1, 0};

inline void Plus(int &x, int y) { x = x + y >= p ? x + y - p : x + y; }

inline int init(int x, int y) { return 1 <= x && 1 <= y && x <= n && y <= m; }

int main()
{
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while(T--)
	{
		memset(bo, 0, sizeof(bo));
		memset(Map, 0, sizeof(Map));
		memset(f, 0, sizeof(f));
		scanf("%d%d%d%d%d", &n, &m, &C, &D, &p);
		for(int i=1; i<=C; ++i)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			Map[x][y] = 1;
		}
		
		f[1][1][1][1][0] = 1;
		que.push(node(1, 1, 1, 1, 0));
		while(!que.empty())
		{
			node U = que.front();
			que.pop();
			for(int i=0; i<2; ++i)
			for(int j=0; j<2; ++j)
			{
				int x1 = U.x1 + dx[i];
				int y1 = U.y1 + dy[i];
				int x2 = U.x2 + dx[j];
				int y2 = U.y2 + dy[j];
				
				if(x1 == x2 && y1 == y2)
					if(x1 != n || y1 != m) continue;
				
				if(!init(x1, y1) || !init(x2, y2)) continue;
				
				int s = U.s + Map[x1][y1] + Map[x2][y2];
				if(s <= D)
				{
					Plus(f[x1][y1][x2][y2][s], f[U.x1][U.y1][U.x2][U.y2][U.s]);
					if(!bo[x1][y1][x2][y2][s])
					{
						bo[x1][y1][x2][y2][s] = 1;
						que.push(node(x1, y1, x2, y2, s));
					}
				}
			}
		}
		
		int res = 0;
		for(int i=0; i<=res; ++i) Plus(res, f[n][m][n][m][i]);
		cout << res / 2  << "\n";
	}
}