#include"bits/stdc++.h"

using namespace std;

int T,n,m,C,D,P;

namespace Subtask1{
	const int N=52;
	bool sp[N][N];
	int n,m,C,D,P,f[N<<1][N][N][N],ans;
	inline void up(int&x,int y){x+=y;x<P?:x-=P;}
	void solve(int _n,int _m,int _C,int _D,int _P){
		n=_n,m=_m,C=_C,D=_D,P=_P;
		memset(sp,0,sizeof(sp));
		for(int i=1,x,y;i<=C;i++)scanf("%d%d",&x,&y),sp[x][y]=true;
		register int i,j,k,t,l,r,w;
		memset(f,0,sizeof(f));
		f[1][1][2][sp[2][1]+sp[1][2]]=1;
		for(i=1;i<n+m-2;i++){
			l=max(1,i+2-m),r=min(i+1,n);
			for(j=l;j<=r;j++)for(k=j+1;k<=r;k++)for(t=0;t<=D;t++)if(f[i][j][k][t]){
				w=f[i][j][k][t];
				up(f[i+1][j][k][t+sp[j][i+3-j]+sp[k][i+3-k]],w);
				if(j!=n)up(f[i+1][j+1][k][t+sp[j+1][i+2-j]+sp[k][i+3-k]],w);
				if(k!=n)up(f[i+1][j][k+1][t+sp[j][i+3-j]+sp[k+1][i+2-k]],w);
				if(j!=n&&k!=n)up(f[i+1][j+1][k+1][t+sp[j+1][i+2-j]+sp[k+1][i+2-k]],w);
			}
		}
		for(ans=i=0;i<=D;i++)up(ans,f[n+m-2][n][n][i]);
		printf("%d\n",ans);
	}
};

namespace Subtask2{
	int n,m,P,ans;
	typedef long long ll;
	int gcd(int x,int y){return y?gcd(y,x%y):x;}
	void exgcd(int a,int b,ll&x,ll&y){
		if(b==0){x=1,y=0;return;}
		exgcd(b,a%b,y,x);y-=a/b*x;
	}
	int inv(int a){
		ll x,y;exgcd(a,P,x,y);
		return (x%P+P)%P;
	}
	int power(int a,int t){
		int r=1;
		while(t){
			if(t&1)r=(ll)r*a%P;
			a=(ll)a*a%P;t>>=1;
		}
		return r;
	}
	int sqr(int x){
		return (ll)x*x%P;
	}
	vector<int>d,t;
	int calc(int n,int m){
		if(n<m)return 0;
		register int r=1,i,j,l,s;
		d.clear(),t.clear();
		for(i=2,s=P;i*i<=s;i++){
			if(s%i==0)d.push_back(i),t.push_back(0);
			while(s%i==0)s/=i;
		}
		if(s^1)d.push_back(s),t.push_back(0); 
		l=d.size();
		for(i=2;i<=m;i++){
			s=i;
			for(j=0;j<l;j++){
				while(s%d[j]==0)t[j]--,s/=d[j];
			}
			r=(ll)r*inv(s)%P;
		}
		for(i=n;i>n-m;i--){
			s=i;
			for(j=0;j<l;j++){
				while(s%d[j]==0)t[j]++,s/=d[j];
			}
			r=(ll)r*s%P;
		}
		for(i=0;i<l;i++)r=(ll)r*power(d[i],t[i])%P;
		return r;
	}
	void solve(int _n,int _m,int _P){
		n=_n,m=_m,P=_P;
		ans=(((ll)calc(n+m-4,n-2)*calc(n+m-4,m-2)-(ll)calc(n+m-4,n-1)*calc(n+m-4,m-1))%P+P)%P;
		printf("%d\n",ans);
	}
};

namespace Subtask3{
	int n,m,P,ans,C,dp[105];
	typedef long long ll;
	int gcd(int x,int y){return y?gcd(y,x%y):x;}
	void exgcd(int a,int b,ll&x,ll&y){
		if(b==0){x=1,y=0;return;}
		exgcd(b,a%b,y,x);y-=a/b*x;
	}
	int inv(int a){
		ll x,y;exgcd(a,P,x,y);
		return (x%P+P)%P;
	}
	int power(int a,int t){
		int r=1;
		while(t){
			if(t&1)r=(ll)r*a%P;
			a=(ll)a*a%P;t>>=1;
		}
		return r;
	}
	int sqr(int x){
		return (ll)x*x%P;
	}
	vector<int>d,t;
	int calc(int n,int m){
		if(n<m)return 0;
		register int i,j,s,l,r=1;
		l=d.size();
		for(i=2;i<=m;i++){
			s=i;
			for(j=0;j<l;j++){
				while(s%d[j]==0)t[j]--,s/=d[j];
			}
			r=(ll)r*inv(s)%P;
		}
		for(i=n;i>n-m;i--){
			s=i;
			for(j=0;j<l;j++){
				while(s%d[j]==0)t[j]++,s/=d[j];
			}
			r=(ll)r*s%P;
		}
		for(i=0;i<l;i++)r=(ll)r*power(d[i],t[i])%P;
		return r;
	}
	typedef pair<int,int>pii;
	vector<pii> ee;
	bool comp(const pii&a,const pii&b){
		return a.first+a.second<b.first+b.second;
	}
	int CCC(int n,int m){
		return (((ll)calc(n+m-4,n-2)*calc(n+m-4,m-2)-(ll)calc(n+m-4,n-1)*calc(n+m-4,m-1))%P+P)%P;
	}
	void solve(int _n,int _m,int _C,int _P){
		n=_n,m=_m,P=_P,C=_C;
		d.clear(),t.clear();
		register int i,s,x,y;
		for(i=2,s=P;i*i<=s;i++){
			if(s%i==0)d.push_back(i),t.push_back(0);
			while(s%i==0)s/=i;
		}
		if(s^1)d.push_back(s),t.push_back(0); 
		for(i=1;i<=C;i++){
			scanf("%d%d",&x,&y);
			ee.push_back(make_pair(x,y));
		}
		sort(ee.begin(), ee.end());
		printf("%d\n",CCC(n,m));
	}
};

int main(){
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d%d%d",&n,&m,&C,&D,&P);
		if(n<=50&&m<=50){Subtask1::solve(n,m,C,D,P);continue;}
		if(C==0){Subtask2::solve(n,m,P);continue;}
		if(D==0){Subtask3::solve(n,m,C,P);continue;}
		puts("0"); 
	}
	return 0;
}
