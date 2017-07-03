#include<bits/stdc++.h>
using namespace std;
const int N=55;
int n,m,c,d,t;
long long p;
int mat[250][250];
int ans;
bool vis[250][250];
int cc;
void dfs2(int x,int y){
	if(x==n&&y==m){
		if(cc<=d)ans++;
	}
	if(vis[x][y]==1) return;
	if(x+1<=n){
		if(mat[x+1][y]==1) cc++;
		dfs2(x+1,y);
		if(mat[x+1][y]==1) cc--;
	}
	if(y+1<=m){
		if(mat[x][y+1]==1) cc++;
		dfs2(x,y+1);
		if(mat[x][y+1]==1) cc--;
	}
}
void dfs(int x,int y){
	if(x==n&&y==m){
		vis[n][m]=0;if(mat[1][2]==1)cc++;dfs2(1,2);if(mat[1][2]==1)cc--;
	}
	if(x+1<=n){
     	if(mat[x+1][y]==1) cc++;vis[x+1][y]=1,dfs(x+1,y),vis[x+1][y]=0;	if(mat[x+1][y]==1) cc--;
	} 
	if(y+1<=m){
		if(mat[x][y+1]==1) cc++;vis[x][y+1]=1,dfs(x,y+1),vis[x][y+1]=0;if(mat[x][y+1]==1) cc--;
	} 
}
int main(){
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	int t=0,x,y;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d%lld",&n,&m,&c,&d,&p);
		memset(mat,0,sizeof(mat));
		for(int i=1;i<=c;i++){
			scanf("%d%d",&x,&y);mat[x][y]=1;
		}
		ans=0;cc=0;
		memset(vis,0,sizeof(vis));
		if(mat[2][1]==1)cc++;
		vis[2][1]=1;
		dfs(2,1);
		printf("%d\n",ans%p);
	}
	return 0;
}

