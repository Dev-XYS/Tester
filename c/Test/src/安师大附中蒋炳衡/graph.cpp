#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
using namespace std;

#define abs(X) ((X)>0?(X):(-(X)))

typedef long long LL;

const int Maxn=1E4+5;

int N,M,Mod;
struct E{
	int v,a,b,nxt;
}adj[Maxn];
int hed[Maxn],TE;
int cnt[Maxn];
int Ans[Maxn];

void addedge(int u,int v,int a,int b){
++TE,adj[TE].a=a,adj[TE].b=b,adj[TE].v=v,adj[TE].nxt=hed[u],hed[u]=TE;}

bool Check(){
	//for(int i=1;i<=3;++i)
	//	cerr<<cnt[i]<<' ';
	//cerr<<endl;
	for(int i=3;i>=1;--i)
		Ans[(i<<1)-1]=cnt[i],Ans[i<<1]=-cnt[i];
	int Val=0,Vala=0,Sum;
	for(int u=1;u<=3;++u){
		for(int k=hed[u];k!=-1;k=adj[k].nxt)
			if(adj[k].v==u%3+1) Val+=Ans[k]*adj[k].b,Vala+=adj[k].a;//cerr<<'a'<<k<<' '<<endl;
		Sum=0;
		for(int k=hed[u];k!=-1;k=adj[k].nxt) Sum+=Ans[k];
		if(Sum%Mod!=0) return false;
	}
	//cerr<<Val<<' '<<Vala<<endl;
	if(Val%Mod!=Vala%Mod) return false;
	return true;
}
		

void Dfs(int i){
	if(i>N){
		if(Check()){
			for(int k=1;k<=3;++k)
				printf("%d\n",(Ans[(k<<1)-1]+5)%5);
			exit(0);
		}
		return;
	}
	for(int j=-4;j<=4;++j){
		cnt[i]=j;
		Dfs(i+1);
	}
	return;
}

int main(){
	freopen("graph.in","r",stdin),
	freopen("graph.out","w",stdout);
	scanf("%d %d %d",&N,&M,&Mod);
	memset(hed,-1,sizeof(hed));
	for(int i=1;i<=M;++i){
		int u,v,a,b;
		scanf("%d %d %d %d",&u,&v,&a,&b);
		addedge(u,v,a,b),addedge(v,u,-a,b);
	}
	Dfs(1);
	return 0;
}

