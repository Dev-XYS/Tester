#include <cstdio>

namespace D7C {
	int n, m, p, cnt = 0;
	int head[110], next[2010], to[2010], a[2010], b[2010], c[2010];
	int visited[110];

	void solve( int t ) {
		for( register int i = head[t]; i; i = next[i] ) {
			if( visited[to[i]] == visited[t] )
				return;
			if( !visited[to[i]] )
				visited[to[i]] = visited[t],
				solve( i );
		}
	}

	bool check( int x, int y, int z ) {
		c[1] = x, c[2] = y, c[3] = z;
		for( register int i = 1; i <= 3; ++i ) {
			int tot = 0;
			for( register int j = head[i]; j; j = next[j] ) {
				tot += c[j],
				tot %= p;
			}
			if( tot != 0 )
				return false;
		}
		int tota[4] = {}, totb[4] = {};
		for( register int i = 1; i <= 3; ++i ) {
			for( register int j = head[i]; j; j = next[j] )
				if( visited[i] == visited[to[j]] )
					tota[visited[i]] += a[j],
					totb[visited[i]] += b[j] * c[j];
		}
		for( register int i = 1; i <= 3; ++i )
			if( tota[i] % p != totb[i] % p )
				return false;
		return true;
	}

	int main() {
		freopen( "graph.in", "r", stdin );
		freopen( "graph.out", "w", stdout );
		scanf( "%d%d%d", &n, &m, &p );
		for( register int i = 1; i <= m; ++i ) {
			int x, y, a, b;
			scanf( "%d%d%d%d", &x, &y, &a, &b );
			next[++cnt] = head[x],
			to[cnt] = y,
			head[x] = cnt,
			D7C::a[cnt] = a,
			D7C::b[cnt] = b;
		}
		cnt = 0;
		for( register int i = 1; i <= n; ++i ) {
			if( !visited[i] )
				visited[i] = ++cnt;
			solve( i );
		}
		if( n == 3 ) {
			for( register int i = 0; i <= 4; ++i ) {
				for( register int j = 0; j <= 4; ++j ) {
					for( register int k = 0; k <= 4; ++k ) {
						if( check( i, j, k ) ) {
							printf( "%d\n%d\n%d\n", i, j, k );
						}
					}
				}
			}
		}
		return 0;
	}
}

int main() {
	D7C::main();
	return 0;
}
