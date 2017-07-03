#include <bits/stdc++.h>
using namespace std;
int f[2][51][51][51],b[51][51];
int n,m,C,D,p;
void baoli()
{
    for (int i=1;i<=n;++i) for (int j=1;j<=m;++j) b[i][j]=0;
    for (int i=1;i<=C;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        b[x][y]=1;
    }
    for (int k=0;k<=1;++k) for (int i=1;i<=n;++i) for (int j=1;j<=n;++j) for (int d=0;d<=D;++d) f[k][i][j][d]=0;
    f[1][1][1][0]=1;
    for (int k=1;k<n+m-1;++k)
    {
        for (int i=1;i<=n;++i) for (int j=1;j<=n;++j) for (int d=0;d<=D;++d) f[(k+1)&1][i][j][d]=0LL;
        for (int i=1;i<=n;++i)
        for (int i1=1;i1<=n;++i1)
        for (int d=0;d<=D;++d)
        {
            int j=k-i+1,j1=k-i1+1;
            if (j>m || j1>m || !j || !j1) continue;
            int x,y,x1,y1,dd;
            x=i+1,y=j,x1=i1+1,y1=j1,dd=d+b[x][y]+b[x1][y1];
            if (x<=n && x1<=n && (x!=x1 || y!=y1 || k==n+m-2) && dd<=D) f[(k+1)&1][x][x1][dd]=(f[(k+1)&1][x][x1][dd]+f[k&1][i][i1][d])%p;
            if (k!=1)
            {
                x=i+1,y=j,x1=i1,y1=j1+1,dd=d+b[x][y]+b[x1][y1];
                if (x<=n && y1<=m && (x!=x1 || y!=y1 || k==n+m-2) && dd<=D) f[(k+1)&1][x][x1][dd]=(f[(k+1)&1][x][x1][dd]+f[k&1][i][i1][d])%p;
            }
            x=i,y=j+1,x1=i1+1,y1=j1,dd=d+b[x][y]+b[x1][y1];
            if (y<=m && x1<=n && (x!=x1 || y!=y1 || k==n+m-2) && dd<=D) f[(k+1)&1][x][x1][dd]=(f[(k+1)&1][x][x1][dd]+f[k&1][i][i1][d])%p;
            x=i,y=j+1,x1=i1,y1=j1+1,dd=d+b[x][y]+b[x1][y1];
            if (y<=m && y1<=m && (x!=x1 || y!=y1 || k==n+m-2) && dd<=D) f[(k+1)&1][x][x1][dd]=(f[(k+1)&1][x][x1][dd]+f[k&1][i][i1][d])%p;
        }
    }
    int ans=0;
    for (int i=0;i<=D;++i) ans=(ans+f[(n+m-1)&1][n][n][i])%p;
    printf("%d\n",ans);
}
void solve()
{
    scanf("%d%d%d%d%d",&n,&m,&C,&D,&p);
    if (p==1) {puts("0");return;}
    if (n<=50 && m<=50 && C<=50) {baoli();return;}
}
int main()
{
    freopen("grid.in","r",stdin);
    freopen("grid.out","w",stdout);
    int T;
    cin>>T;
    while (T--) solve();
}
