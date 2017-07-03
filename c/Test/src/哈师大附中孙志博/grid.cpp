#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N=54;
int n,m,C,D,P;
bool map[N][N]; int f[N<<1][N][N][N];
int readin() {
	int x=0,f=1; char ch=getchar();
	while(ch>'9'||ch<'0') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void read() {
	n=readin(),m=readin();
	C=readin(),D=readin(),P=readin();
	D=min(D,C);
	memset(map,0,sizeof map);
	for (int x,y,i=1;i<=C;i++) {
		x=readin(),y=readin();
		map[x][y]=1;
	}
	return;
}
void dp() {
	int w;
	memset(f,0,sizeof f);
	f[1][1][2][map[1][2]+map[2][1]]=1;
	for (int i=2;i<n+m-2;i++) {
		int lim=min(i,m);
		for (int j=1;j<lim;j++)
		for (int k=j+1;k<=lim;k++)
		for (int d=0;d<=D;d++)
			if (f[i-1][j][k][d]) {
				if (j<m) {
					w=map[i+1-j][j+1];
					if (k<m)
						(f[i][j+1][k+1][d+w+map[i+1-k][k+1]]+=f[i-1][j][k][d])%=P;
					if (k>j+1)
						(f[i][j+1][k][d+w+map[i+2-k][k]]+=f[i-1][j][k][d])%=P;
				}
				if (i+1-j<n) {
					w=map[i+2-j][j];
					if (k<m)
						(f[i][j][k+1][d+w+map[i+1-k][k+1]]+=f[i-1][j][k][d])%=P;
					if (k>j)
						(f[i][j][k][d+w+map[i+2-k][k]]+=f[i-1][j][k][d])%=P;
				}
			}
	}
	int ans=0;
	for (int i=0;i<=D;i++)
		(ans+=f[n+m-3][m-1][m][i])%=P;
	printf("%d\n",ans);
	return;
}
int main() {
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	for (int i=readin();i;i--)
		read(),dp();
	return 0;
}