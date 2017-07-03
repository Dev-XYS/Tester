#include <cstdio>

namespace D7C {
	int T, n, m, c, d, mod;
	int map[36][36] = {};
	bool visited[36][36] = {};
	int ans = 0, cnt = 0; 
	
	void the_first( int x, int y, int z );
	void the_second( int x, int y, int z );
	
	int main() {
		freopen( "grid.in", "r", stdin );
		freopen( "grid.out", "w", stdout);
		scanf( "%d", &T );
		while( T-- ) {
			scanf( "%d%d%d%d%d", &n, &m, &c, &d, &mod );
			for( register int i = 1; i <= n; ++i )
				for( register int j = 1; j <= m; ++j )
					map[i][j] = 0;
			for( register int i = 1; i <= c; ++i ) {
				int x, y;
				scanf( "%d%d", &x, &y );
				map[x][y] = -1;
			}
			ans = 0;
			for( register int i = 1; i <= n; ++i )
				for( register int j = 1; j <= m; ++j )
					visited[i][j] = 0;
			the_first( 1, 1, 0 );
			printf( "%d\n", ( ans % mod ) / 2 );
		}
		return 0;
	} 
	
	inline void the_first( int x, int y, int z ) {
		if( visited[x][y] )
			return;
		if( x == 1 && y == 1 ) {
			the_first( x + 1, y, z );
			the_first( x, y + 1, z );
			return;
		}
		if( map[x][y] == -1 ) {
			if( z + 1 > d )
				return;
			visited[x][y] = 1;
			if( x < n )
				the_first( x + 1, y, z + 1 );
			if( y < m )
				the_first( x, y + 1, z + 1 );
			visited[x][y] = 0;
			return;
		}
		if( x == n && y == m ) {
			cnt = 0;
			the_second( 1, 1, z );
			ans += cnt;
			ans %= mod;
			return;
		}
		visited[x][y] = 1;
		if( y < m )
			the_first( x, y + 1, z );
		if( x < n )
			the_first( x + 1, y, z );
		visited[x][y] = 0;
		return;
	}
	
	inline void the_second( int x, int y, int z ) {
		if( visited[x][y] )
			return;
		if( x == 1 && y == 1 ) {
			the_second( x + 1, y, z );
			the_second( x, y + 1, z );
			return;
		}
		if( map[x][y] == -1 ) {
			if( z + 1 > d )
				return;
			visited[x][y] = 1;
			the_second( x + 1, y, z + 1 );
			the_second( x, y + 1, z + 1 );
			visited[x][y] = 0;
			return;
		}
		if( x == n && y == m ) {
			++cnt;
			cnt %= mod;
			return;
		}
		visited[x][y] = 1;
		if( y < m )
			the_second( x, y + 1, z );
		if( x < n )
			the_second( x + 1, y, z );
		visited[x][y] = 0;
		return;
	}
}

int main() {
	D7C::main();
	return 0;
}
