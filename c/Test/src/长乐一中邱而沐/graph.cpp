#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 100
using namespace std;

int n, m, p;
int a[N][N], b[N][N], c[N][N], x[N], y[N];

inline void check()
{
	for(int i=1; i<=n; ++i)
	{
		int s = 0;
		for(int j=1; j<=n; ++j)
			if(i != j) s += c[i][j];
		if(s % p) return;
	}
	
	int s1 = 0, s2 = 0;
	for(int i=1; i<=n; ++i)
	{
		int j = i + 1;
		if(j > n) j = 1;
		s1 += b[i][j] * c[i][j];
		s2 += a[i][j];
	}
	if((s1 % p + p) % p != (s2 % p + p) % p) return;
	
	for(int i=1; i<=m; ++i)
		cout << c[x[i]][y[i]] << "\n";
	exit(0);
}

void dfs(int k)
{
	if(k > n) check();
	else for(int i=0; i<p; ++i)
	{
		c[x[k]][y[k]] = i;
		c[y[k]][x[k]] = -i;
		dfs(k + 1);		
	}
}

int main()
{
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
	
	scanf("%d%d%d", &n, &m, &p);
	for(int i=1; i<=m; ++i)
	{
		scanf("%d%d", &x[i], &y[i]);
		scanf("%d%d", &a[x[i]][y[i]], &b[x[i]][y[i]]);	
		a[y[i]][x[i]] = -a[x[i]][y[i]];
		b[y[i]][x[i]] = b[x[i]][y[i]];
	}
	dfs(1);
}