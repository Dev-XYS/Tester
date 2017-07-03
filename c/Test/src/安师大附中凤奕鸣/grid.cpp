#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int n,m,c,d,mod;
int g[52][52],inv[100010],ifc[100010],fac[100010],f[52][52][52][52];
void __(){
	 inv[0]=1;
	 inv[1]=1;
	 ifc[0]=1;
	 ifc[1]=1;
	 fac[0]=1;
	 fac[1]=1;
	 for (int i=2;i<min(mod,100010);i++){
		 inv[i]=(long long)(mod-mod/i)*inv[mod%i]%mod;
		 ifc[i]=(long long)ifc[i-1]*inv[i]%mod;
		 fac[i]=(long long)fac[i-1]*i%mod;
     }
}
int work(){
	int i,j,k,l,o,res=0;
	memset(f,0,sizeof(f));
	f[1][1][1][0]=1;
	for (i=1;i<=n;i++){
		for (j=1;j<=m;j++){
			for (k=j+(i!=n||j!=m);k<=m;k++){
				for (l=0;l<=d;l++){
					f[i][j][k][l]=((l>=g[i][k]+g[i][j]&&i>1)?f[i-1][j][k][l-g[i][k]-g[i][j]]:0);
					//cerr<<i<<" "<<j<<" "<<k<<" "<<l<<" : "<<f[i][j][k][l]<<endl;
				}
			}
		}
		for (j=1;j<=m;j++){
			for (k=j+(i!=n||j!=m);k<=m;k++){
				for (l=0;l<=d;l++){
					f[i][j][k][l]=(f[i][j][k][l]+(long long)((l>=g[i][j]&&j>1)?f[i][j-1][k][l-g[i][j]]:0))%mod;
					//cerr<<i<<" "<<j<<" "<<k<<" "<<l<<" : "<<f[i][j][k][l]<<endl;
				}
			}
		}
		for (j=1;j<=m;j++){
			for (k=j+(i!=n||j!=m);k<=m;k++){
				for (l=0;l<=d;l++){
					f[i][j][k][l]=(f[i][j][k][l]+(long long)((l>=g[i][k]&&k>1)?f[i][j][k-1][l-g[i][k]]:0))%mod;
					//cerr<<i<<" "<<j<<" "<<k<<" "<<l<<" : "<<f[i][j][k][l]<<endl;
				}
			}
		}
	}
	for (i=0;i<=d;i++){
		res=(res+f[n][m][m][i])%mod;
	}
	return res;
}
int _(int x,int y){
	return (long long)fac[x]*ifc[y]%mod*ifc[x-y]%mod;
}
int calc(){
	int x=n+m-3,y=n-1;
	return (long long)_((x-1)%mod,(y-1)%mod)*_(x%mod,(y-1)%mod)%mod*inv[y%mod]%mod;
}
int main(){
	int i,o,x,y;
	freopen ("grid.in","r",stdin);
	freopen ("grid.out","w",stdout);
	scanf ("%d",&o);
	while (o--){
		  scanf ("%d%d%d%d%d",&n,&m,&c,&d,&mod);
		  if (n<=50&&m<=50&&c<=50){
		  	 memset(g,0,sizeof(g));
		  	 for (i=1;i<=c;i++){
		  	 	 scanf ("%d%d",&x,&y);
		  	 	 g[x][y]=1;
		  	 }
		  	 printf ("%d\n",work());
		  }
		  else{
		  	   __();
			   printf ("%d\n",calc());
		  }
	}
	return 0;
}

