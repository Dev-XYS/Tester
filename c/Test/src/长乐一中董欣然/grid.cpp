#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int dir[3][2];
int f[105][51][51][51],bo[51][51];
int T,n,m,C,D,mod,ans,step;
void DP()
{
//	memset(f,0,sizeof(f));		//(0,0) => (n-1,m-1)
	step=n-1+m-1;
	for (int len=0; len<=step; ++len)
		for (int i=0; i<=n; ++i)
			for (int h=i; h<=n; ++h)
			for (int c=0; c<=D; ++c) f[len][i][h][c]=0;			
	f[0][0][0][0]=1;	
	for (int len=0; len<step; ++len){
		for (int i=0; i<n; ++i){
			int j=len-i;
			for (int h=i; h<n; ++h){
				int k=len-h;
				for (int c=0; c<=D; ++c)
				if (f[len][i][h][c]){
					for (int d1=0; d1<=1; ++d1)
					  for (int d2=0; d2<=1; ++d2){
							int x=i+dir[d1][0], y=j+dir[d1][1];
							int u=h+dir[d2][0], v=k+dir[d2][1];
					//		printf("s");
							if (x==u && y==v) continue;
							if (x>=n || y>=m || u>=n || v>=m) continue;
							int d=c+bo[x][y]+bo[u][v];
							if (d>D) continue;
						//	printf("%d %d %d %d  %d %d %d %d \n",len+1,x,u,d, len,i,h,c);
							(f[len+1][x][u][d]+=f[len][i][h][c])%=mod;
					  }
				}
			}
		}
	}
}
int main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
//	freopen("grid2.in","r",stdin);
	dir[0][0]=0; dir[0][1]=1;
	dir[1][0]=1; dir[1][1]=0;
	scanf("%d",&T);
	while (T--){
		memset(bo,0,sizeof(bo));
		scanf("%d%d%d%d%d",&n,&m,&C,&D,&mod);
		for (int i=1; i<=C; ++i){
			int x,y;
			scanf("%d%d",&x,&y);
			bo[x-1][y-1]=1;
		}
		if (n==1 && m==1){
			printf("%d\n",1%mod); continue;
		}
		if (n==1){
			printf("%d\n",(m==2?1:0)%mod); continue;
		}
		if (m==1){
			printf("%d\n",(n==2?1:0)%mod); continue;
		}
		DP();
		ans=0;
		for (int c=0; c<=D; ++c) (ans+=f[step-1][n-2][n-1][c])%=mod;
		printf("%d\n",ans);
	}
}
