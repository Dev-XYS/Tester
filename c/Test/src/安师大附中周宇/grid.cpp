#include<map>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;

const int Maxn=55;
const int INF=0x3f3f3f3f;

int N,M,C,D,Mod;
map<int,int> Map[Maxn];
int f[Maxn<<1][Maxn][Maxn][Maxn];

int Pow_Mod(int X,int K){
	int val=1,tmp=X;
	while(K){
		if(K&1) val=(LL)val*tmp%Mod;
		tmp=(LL)tmp*tmp%Mod; K>>=1;
	}
	return val;
}

void PrePare(){
	
}

void Work(){
	memset(f,0,sizeof(f));
	scanf("%d %d %d %d %d",&N,&M,&C,&D,&Mod);
	for(int i=1;i<=C;++i){
		int x,y;
		scanf("%d %d",&x,&y);
		Map[x][y]=1;
	}
	if(Mod==1){puts("0");return;}
	f[0][0][0][0]=1;
	for(int i=1;i<=N-1+M-1;++i)
		for(int j=max(0,i-M+1);j<=min(i,N-1);++j)
			for(int k=max(0,i-M+1);k<=min(i,N-1);++k){
				int tmp=0;
				int x1=1+j,y1=1+i-j,x2=1+k,y2=1+i-k;
				if(j==k&&(!(x1==N&&y1==M))) continue;
				tmp+=(Map[x1].find(y1)!=Map[x1].end());
				tmp+=(Map[x2].find(y2)!=Map[x2].end());
				for(int x=tmp;x<=D;++x){
					if(j>0&&k>0) (f[i][j][k][x]+=f[i-1][j-1][k-1][x-tmp])%=Mod;
					if(j>0&&i-k>0) (f[i][j][k][x]+=f[i-1][j-1][k][x-tmp])%=Mod;
					if(i-j>0&&k>0) (f[i][j][k][x]+=f[i-1][j][k-1][x-tmp])%=Mod;
					if(i-j>0&&i-k>0) (f[i][j][k][x]+=f[i-1][j][k][x-tmp])%=Mod;
				}
			}
	int Ans=0;
	for(int x=0;x<=D;++x)
		(Ans+=f[N-1+M-1][N-1][N-1][x])%=Mod;
	for(int i=1;i<=N;++i)
		Map[i].clear();
	if(Mod%2==0) printf("%d\n",Ans>>1);
	else printf("%lld\n",(LL)Ans*Pow_Mod(2,Mod-2)%Mod);
}

int main(){
	freopen("grid.in","r",stdin),
	freopen("grid.out","w",stdout);
	int Test;
	scanf("%d",&Test);
	while(Test--) Work();
	return 0;
}

