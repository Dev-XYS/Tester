#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int inf = 1e9+7;
int n, m, ans, tot;
int vis[60][60];
int map[60][60];
void solve2(int x, int y, int t){
	if(x == n && y == m){
		tot++;
		return;
	}
	vis[x][y] = 1;
	if(x+1 <= n && ! vis[x+1][y]){
		if(!map[x+1][y]) solve2(x+1, y, t);
		else
			if(t)	solve2(x+1, y, t-1);
	}
	if(y+1<=m && !vis[x][y+1]){
		if(!map[x][y+1])	solve2(x, y+1, t);
		else
			if(t)	solve2(x, y+1, t-1);
	}
	vis[x][y]=0;
	return;
}
void solve1(int x,int y,int t){
	if(x==n && y==m){
		tot=0;
		solve2(1, 1, t);
		ans += tot;
		return;
	}
	vis[x][y]=1;
	if(y+1 <= m && !vis[x][y+1]){
		if(!map[x][y+1])	solve1(x, y+1, t);
		else
			if(t)	solve1(x, y+1, t-1);
	}	
	if(x+1<=n && !vis[x+1][y]){
		if(!map[x+1][y])	solve1(x+1, y, t);
		else
			if(t)	solve1(x+1,y,t-1);
	}
	vis[x][y] = 0;
	return;
}
int main(){
	int a, b;
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	int T,C,D,P;
	scanf("%d",&T);
	while(T--){
		memset(vis,0,sizeof(vis));
		memset(map,0,sizeof(map));
		ans=0;
		scanf("%d%d%d%d%d", &n, &m, &C, &D, &P);
		for(int i=1; i<=C; i++){
			scanf("%d%d", &a, &b);
			map[a][b] = 1;
		}
		solve1(1, 1, D);
		cout<< ( ans/2 ) %P<<endl;
	}
	return 0;
} 
