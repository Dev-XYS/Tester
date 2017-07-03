#include <bits/stdc++.h>

using namespace std;

int add(int x,int y,int z){
	x += y;while (x >= z) x -= z;
	return x;
}
int f[110][60][60][210],mp[51][51];
int T,n,m,C,D,mod;
void solve1();
int main(){
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	scanf("%d",&T);
	while (T--){
		scanf("%d%d%d%d%d",&n,&m,&C,&D,&mod);
		if (n <= 50) solve1();
		/*
		for (int i = 1;i <= n;i++) {
			for (int j = 1;j <= m;j++)
				printf("%d ",f[i+j-1][i-1][i][0]);
			printf("\n");
		}*/
	}
	return 0;
}
void solve1(){
	
	for (int i = 0;i <= n+m;i++) 
		for (int j = 0;j <= n;j++) 
			for (int k = 0;k <= m;k++) 
				for (int l = 0;l <= C;l++) 
					f[i][j][k][l] = 0;
	memset(mp,0,sizeof(mp));
	for (int i = 1;i <= C;i++){
		int x,y;scanf("%d%d",&x,&y);
		mp[x][y] = 1;
	}
	int cnt = mp[1][1]+mp[1][2]+mp[2][1];
	if (n == 1 && m == 1){
		printf("%d\n",D == C);
		return;
	}
	else if (n == 1 || m == 1) {
		printf("0\n");
		return;
	}
	else{
		f[3][1][2][cnt] = 1;
		for (int i = 3;i < n+m-1;i++){
			for (int j = 1;j <= min(n,i);j++)
				for (int k = j+1;k <= min(n,i);k++)
					for (int l = 0;l <= C;l++){
//						printf("%d %d %d %d\n",i,j,k,l);
						
						if (k < n && max(i-j,i-k) <= m){
							int w = l+mp[j+1][i-j]+mp[k+1][i-k];
//							cout << w << endl;
							f[i+1][j+1][k+1][w] = add(f[i+1][j+1][k+1][w],f[i][j][k][l],mod);
						}

						if (max(i-j,i-k)+1 <= m){
							int w = l+mp[j][i-j+1]+mp[k][i-k+1];
//							cout << "GG\n";
//							printf("%d %d %d %d %d\n",i,j,k,l,mod);
							f[i+1][j][k][w] = add(f[i+1][j][k][w],f[i][j][k][l],mod);
						}
//						cout <<"GG\n";						
						if (j < k-1 && i-k < m && i-j <= m){
							int w = l+mp[j+1][i-j]+mp[k][i-k+1];
							f[i+1][j+1][k][w] = add(f[i+1][j+1][k][w],f[i][j][k][l],mod);							
						}
						if (i-j <m && k < n){
							int w = l+mp[j][i-j+1]+mp[k+1][i-k];
							f[i+1][j][k+1][w] = add(f[i+1][j][k+1][w],f[i][j][k][l],mod);							
						}						
					}
		}
		int ans = 0;
		for (int i = 0;i <= D;i++) 
			ans = add(ans,f[n+m-1][n-1][n][i],mod);
		printf("%d\n",ans);
	}
}
