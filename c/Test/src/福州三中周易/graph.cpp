#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
#define fir first
#define sec second
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){ return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){ return a<b?a=b,1:0;}
int n,m;ll p;
#define N 233
#define M 5000 
ll mul(ll a,ll n){
	if(n<0)n+=p;
	ll res=0;
	for(;n;n>>=1,a=a+a>p?a+a-p:a+a) 
		if(n&1)res=res+a>p?res+a-p:res+a;
	return res;
}
ll exp(ll a,ll n){
	ll res=1;
	for(;n;n>>=1,a=mul(a,a))
		if(n&1)res=mul(res,a);
	return res; 
}
struct edge{
	int to,nxt;ll a,b;
}e[M];int cnt,lst[N],u[M],v[M];ll a_[M],b[M];
void ins(int a,int b,ll c,ll d){
	e[++cnt]=(edge){b,lst[a],c,d};lst[a]=cnt;
}
void lnk(int a,int b,ll c,ll d){
	ins(a,b,c,d);
	ins(b,a,p-c,d);
}
ll a[N][N],x[N];
void swap(int x,int y,int r){for(int i=0;i<r;i++)swap(a[i][x],a[i][y]);}
void gauss(int n){
    int r=0,c=0;
    for(;r<n&&c<n;r++,c++){
        int pivot=r;
        for(int i=r+1;i<n;i++)
			if(abs(a[i][c])>abs(a[pivot][c]))pivot=i;
        if(pivot!=r)
			swap(a[pivot],a[r]);
        if(!a[r][c]){r--;continue;}
        for(int i=r+1;i<n;i++){
            if(!a[i][c])continue;
            ll t1=a[r][c],t2=a[i][c];
            for(int j=c;j<=n;j++){
            	a[i][j]=(p-mul(a[r][j],t2)+mul(a[i][j],t1))%p;
                //a[i][j]=((ll)a[i][j]*t1-(ll)a[r][j]*t2)%mod;
                //if(a[i][j]<0)a[i][j]+=mod;
            }
        }
    }
    for(int i=r;i<n;i++)if(a[i][n])return;
    for(int i=0,j;i<n&&j<n;i++){
        if(!a[i][i]){
            for(j=i+1;j<n;j++)if(a[i][j])break;
            if(j<n)swap(i,j,n);
        }
    }
    for(int i=n-1;~i;i--){
        ll t=a[i][n];
        for(int j=i+1;j<n;j++)
        	t=(p-mul(a[i][j],x[j])+t)%p;
        x[i]=mul(t,exp(a[i][i],p-2))%p;
    }
}
int main(){
	int i;FO(graph);
	scanf("%d%d%lld",&n,&m,&p);
	for(i=1;i<=m;i++){
		scanf("%d%d%lld%lld",&u[i],&v[i],&a_[i],&b[i]);
		lnk(u[i],v[i],a_[i],b[i]);
	}
    //cerr<<"suc";
	for(int q=2;q<=n;q++){
		ll c=0,ds=0;int i;
		for(i=lst[q];i;i=e[i].nxt){
			c=(c+mul(e[i].a,exp(e[i].b,p-2)))%p;
			ds=(ds+exp(e[i].b,p-2))%p;
		}
		a[q-2][n-1]=p-c;//constant
		a[q-2][q-2]=p-ds;
		for(i=lst[q];i;i=e[i].nxt){
			int b=e[i].to;
			if(b!=1)a[q-2][b-2]=exp(e[i].b,p-2);
		}
	} 
    gauss(n-1);
    for(i=n-1;~i;i--)x[i+2]=x[i];x[1]=0;
	//for(i=1;i<=n;i++)printf("f[%d] = %d\n",i,x[i]);
	for(i=1;i<=m;i++){
		ll ans=mul(((p-x[u[i]]+x[v[i]])%p+a_[i])%p,exp(b[i],p-2));
		printf("%lld\n",ans);
	}
	return 0;
}

