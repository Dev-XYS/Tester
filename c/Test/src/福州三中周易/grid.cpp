#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
#define fir first
#define sec second
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){ return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){ return a<b?a=b,1:0;}
#define N 888
int T,n,m,C,D,p,x[N],y[N],f[6][6][6][6][36][36];
int mp[6][6];
int main(){
	int i,j,x,y,a,b;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d%d%d",&n,&m,&C,&D,&p);
		memset(mp,0,sizeof(mp));
		for(i=1;i<=C;i++)scanf("%d%d",x+i,y+i),mp[x[i]][y[i]]=1;
		puts("lan de xie baoli le");
	}
	return 0;
}

