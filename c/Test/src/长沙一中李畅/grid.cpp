#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define LL long long

const int Maxn = 205;

inline int read(){
	int x = 0,f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch <= '9' && ch >= '0') 
		x = x*10+ch-'0',ch = getchar();
	return x * f;
}

int N,M,C,D,MOD,n,Case;
int fc[15][200005];

inline void upd(int &x,int y){
	x += y;
	if(x >= MOD)  x -= MOD;
}

struct Prim{
	int P,val;
}P[15];

struct data{
	int x,y;
	bool operator <(const data &A)const {
		return x == A.x ? y < A.y : x < A.x;
	}
}Q[Maxn];

void Init(int x){
	n = 0;
	for(int i = 2 ; i*i <= x ; ++i) if(!(x % i)){
		P[++n].P = i; P[n].val = 1;
		while(!(x % i)) P[n].val *= i,x /= i;
	}
	if(x != 1) P[++n] = (Prim){x,x};

	for(int i = 1 ; i <= n ; ++i){
		fc[i][0] = 1;
		for(int j = 1 ; j <= P[i].val && j <= N + M ; ++j)
			if(j % P[i].P) fc[i][j] = (LL)fc[i][j-1]*j%P[i].val;
			else fc[i][j] = fc[i][j-1];
	}
}
 
int fpm(int x,int y,int mod){
	int ret = 1;
	for( ; y ; y >>= 1,x = (LL)x*x%mod)
		if(y & 1) ret = (LL)ret * x % mod;
	return ret;
}
 
void Exgcd(int a,int b,LL &x,LL &y){
	if(!b){x = 1; y = 0; return;}
	Exgcd(b , a%b , y , x); y -= x *(a/b);
}
 

int Inv(int x,int mod){
	LL t1 , t2;
	Exgcd(x , mod , t1 , t2);
	return ((t1%mod) + mod) %mod;
}

void Solve(int &ans,int &mi,int n,int k){
	ans = 1; mi = 0; int tmp;
	while(n){
		tmp = n / P[k].val;
		ans = (LL)fpm(fc[k][P[k].val],tmp,P[k].val)*
			fc[k][n%P[k].val]%MOD * ans%MOD;
		mi += n / P[k].P;
		n /= P[k].P;
	}
}

int Comb(int L,int M){
	static int ret[15]; 
	int tmp , mi , u , v;
	for(int i = 1 ; i <= n ; ++i){
		Solve(tmp , mi , L , i);
		Solve(u , v , M , i);
		mi -= v; 
		tmp = (LL)tmp*Inv(u,P[i].val)%P[i].val;
		Solve(u , v , L - M , i);
		mi -= v; 
		tmp = (LL)tmp*Inv(u,P[i].val)%P[i].val;
		ret[i] = (LL)tmp*fpm(P[i].P,mi,P[i].val)%P[i].val;
	}

	int ans = 0;
	for(int i = 1 ; i <= n ; ++i)
		upd(ans , (LL)ret[i]*(MOD/P[i].val)%MOD
			*Inv(MOD/P[i].val , P[i].val)%MOD);
	return ans;
}

int f[Maxn],g[Maxn];
int dp1[Maxn],dp2[Maxn];
 
inline int calc(int i,int j){
	return Comb(Q[i].x-Q[j].x+Q[i].y-Q[j].y,Q[i].x-Q[j].x);
}

void Calc(int *dp,int fx,int fy,int ex,int ey){
	static int F[Maxn][Maxn];
	memset(F , 0 , sizeof(F));
	int done = 2;
	Q[0] = (data){fx,fy}; 
	Q[C + 1] = (data){ex,ey};
	F[0][1] = 1;

	for(int i = 1 ; i <= C + 1; ++i)
	for(int j = 0 ; j < i ; ++j)
		if(Q[i].x >= Q[j].x  && Q[i].y >= Q[j].y)
			for(int k = 1 ; k <= j + 1; ++k)
				if(F[j][k]) upd(F[i][k+1],(LL)F[j][k]*calc(i,j)%MOD);

	memset(dp , 0 , sizeof(dp));
	for(int i = C + 2 ; ~i ; --i){
		dp[i] = F[C + 1][i];
		for(int j = i + 1 ; j <= C + 2 ; ++j)
			upd(dp[i] , MOD - dp[j]);
	}
	for(int i = 2 ; i <= C + 2 ; ++i)
		dp[i-2] = dp[i],dp[i] = 0;
}

int main(){
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	Case = read();
	while(Case--){
		N = read(); M = read(); C = read(); 
		D = read(); MOD = read(); Init(MOD);
		for(int i = 1 ; i <= C ; ++i)
			Q[i].x = read(),Q[i].y = read();
		sort(Q + 1 , Q + C + 1);

		Calc(f , 1 , 2 , N,M-1);
		Calc(g , 2 , 1 , N-1,M);
		memset(dp1 , 0 , sizeof(dp1));
		for(int i = 0 ; i <= D ; ++i)
			for(int j = 0 ; j <= D - i ; ++j)
				upd(dp1[i+j],(LL)f[i]*g[j]%MOD);

		Calc(f , 1 , 2 , N-1,M);
		Calc(g , 2 , 1 , N,M-1);
		memset(dp2 , 0 , sizeof(dp2));
		for(int i = 0 ; i <= D ; ++i)
			for(int j = 0 ; j <= D - i ; ++j)
				upd(dp2[i+j],(LL)f[i]*g[j]%MOD);

		int ans = 0;
		for(int i = 0 ; i <= D ; ++i)
			upd(ans , dp2[i]),upd(ans  , MOD - dp1[i]);
		printf("%d\n",ans);
	}
	return 0;
}
