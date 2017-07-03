#include <bits/stdc++.h>
#define ll long long
using namespace std;
int dp[101][51][51][51];
bool ban[51][51];
ll fac[200005],inv[200005],pp;
int a[200005],b[200005];
inline ll ksm(ll a,ll b)
{ll res=1ll,tp=a;
while (b)
{if (b&1ll) {res*=tp;res%=pp;}
tp*=tp;tp%=pp;b>>=1ll;
}
return res;
}
int gcd(int a,int b)
{if (a%b==0) return b;
return gcd(b,a%b);
}
inline ll cal(int n,int m)
{/*int i,j,cnt=0;
for (i=n;i>=n-m+1;i--) {a[++cnt]=i;}
for (j=2;j<=m;j++)
{int tp=j;
for (i=1;i<=cnt;i++)
{int t=gcd(tp,a[i]);
if (t>1) 
{tp/=t;a[i]/=t;
if (tp==1) {break;}
}
}
}
ll ans=1ll;
for (i=1;i<=cnt;i++)
{ans*=((ll)(a[i]));ans%=pp;}
return ans;
*/
return (((fac[n]*inv[n-m])%pp)*inv[m])%pp;
}
inline void orz_zy(int n,int m)
{int i;
fac[0]=1ll;inv[0]=1ll;
for (i=1;i<=n+m;i++)
{fac[i]=(fac[i-1]*((ll)(i)))%pp;
inv[i]=ksm(fac[i],pp-2ll);
}
ll ans=cal(n+m-4,n-2);
ans*=cal(n+m-3,n-2);ans%=pp;
ans*=ksm(n-1,pp-2);ans%=pp;
printf ("%lld\n",ans);
}
int main (){
	freopen ("grid.in","r",stdin);
	freopen ("grid.out","w",stdout);
	int test,i,j,k,l,p,q,x,y,n,m,c,d,mod;
	scanf ("%d",&test);
	while (test--)
	{scanf ("%d%d%d%d%d",&n,&m,&c,&d,&mod);
	if (n>50&&m>50&&c==0) {pp=((ll)mod);orz_zy(n,m);continue;}
	memset (ban,0,sizeof(ban));
	memset (dp,0,sizeof(dp));
	for (i=1;i<=c;i++)
	{scanf ("%d%d",&x,&y);
	ban[x][y]++;
	}
	dp[0][1][1][0]=1;
	for (p=1;p<=n+m-2;p++)
	{for (i=max(1,p-m+2);i<=n;i++)
	{j=p-i+2;
	for (k=max(1,p-m+2);k<=i;k++)
	{l=p-k+2;
	if (i==k&&p!=n+m-2) {continue;}
	int ndb=0;
	if (ban[i][j]) {ndb++;}
	if (ban[k][l]) {ndb++;}
	for (q=ndb;q<=d;q++)
	{dp[p][i][k][q]+=dp[p-1][i-1][k][q-ndb];
	if (dp[p][i][k][q]>=mod) {dp[p][i][k][q]-=mod;}
	dp[p][i][k][q]+=dp[p-1][i][k][q-ndb];
	if (dp[p][i][k][q]>=mod) {dp[p][i][k][q]-=mod;}
	dp[p][i][k][q]+=dp[p-1][i-1][k-1][q-ndb];
	if (dp[p][i][k][q]>=mod) {dp[p][i][k][q]-=mod;}
	dp[p][i][k][q]+=dp[p-1][i][k-1][q-ndb];
	if (dp[p][i][k][q]>=mod) {dp[p][i][k][q]-=mod;}
	}
	}
	}
	}
	int ans=0;
	for (i=0;i<=d;i++)
	{ans+=dp[n+m-2][n][n][i];
	if (ans>=mod) {ans-=mod;}
	}
	printf ("%d\n",ans);
	}
	return 0;
}
	
