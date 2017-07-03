#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cmath>

using namespace std;
typedef long long LL;
const int N=101;
const int dx[]={0,-1};
const int dy[]={-1,0};

int n,m,c,d,wz[N][2],t,mod;
int ok[N][N],f[N][N][N][N/2];

int main(){
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	
	int i,j,k,h,g,ans;
	scanf("%d",&t);
	while(t--){
		memset(ok,0,sizeof(ok));
		memset(f,0,sizeof(f));
		scanf("%d%d%d%d%d",&n,&m,&c,&d,&mod);
		for(i=1;i<=c;i++){
			scanf("%d%d",&wz[i][0],&wz[i][1]);
			ok[wz[i][0]][wz[i][1]]=1;
		}
		f[1][n][n][0]=1;
		for(i=2;i<=n+m-1;i++){
			for(j=1;j<=n+m-1;j++){
				if(i+j-n-1&1)continue;
				int x1=(i+j-n-1)/2,y1=x1-i+1;
				swap(x1,y1),x1=-x1+1,y1++;
				if(x1<1||x1>n||y1<1||y1>m)continue;
				for(k=j;k<=n+m-1;k++){
					if((i!=n+m-1&&j==k)||(i+k-n-1&1))continue;
					int x2=(i+k-n-1)/2,y2=x2-i+1,tmp;
					swap(x2,y2),x2=-x2+1,y2++;
					if(x2<1||x2>n||y2<1||y2>m)continue;
					tmp=ok[x1][y1]+ok[x2][y2];
					for(h=tmp;h<=d;h++){
						for(g=0;g<4;g++){
							int tx1=x1+dx[g&1],ty1=y1+dy[g&1];
							int tx2=x2+dx[(g&2)==2],ty2=y2+dy[(g&2)==2];
							if(tx1<1||tx1>n||ty1<1||ty1>m)continue;
							if(tx2<1||tx2>n||ty2<1||ty2>m)continue;
							int t_x=n-tx1+ty1,t_y=n-tx2+ty2;
							f[i][j][k][h]+=f[i-1][t_x][t_y][h-tmp];
							while(f[i][j][k][h]>mod)f[i][j][k][h]-=mod;
						}
					}
				}
			}
		}
		for(ans=0,g=0;g<=d;g++)ans=(ans+f[n+m-1][m][m][g])%mod;
		printf("%d\n",ans);
	}

	return 0;
}

