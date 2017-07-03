#include <bits/stdc++.h>
using namespace std;
#define N 105
int fa[N][N],fb[N][N],fc[N][N];
int n,m,p;
int a[N],b[N];
int main()
{
    freopen("graph.in","r",stdin);
    freopen("graph.out","w",stdout);
    cin>>n>>m>>p;
    for (int i=1;i<=m;++i)
    {
        int lena,lenb;
        scanf("%d%d%d%d",&a[i],&b[i],&lena,&lenb);
        lena%=p;lenb%=p;
        fa[a[i]][b[i]]=lena;fa[b[i]][a[i]]=(-lena+p+p)%p;
        fb[a[i]][b[i]]=fb[b[i]][a[i]]=lenb;
    }
    int yzh=0;
    for (int c1=0;c1<p;++c1)
        for (int c2=0;c2<p;++c2)
            for (int c3=0;c3<p;++c3)
            {
                if (yzh) break;
                int t1,t2;
                t1=(fb[1][2]*c1%p+fb[2][3]*c2%p+fb[3][1]*c3%p)%p;
                t2=(fa[1][2]+fa[2][3]+fa[3][1])%p;
                if (t1==t2) {yzh=1;fc[1][2]=c1;fc[2][3]=c2;fc[3][1]=c3;}
            }
    fc[2][1]=(-fc[1][2]+p+p)%p;
    fc[3][2]=(-fc[2][3]+p+p)%p;
    fc[1][3]=(-fc[3][1]+p+p)%p;
    for (int i=1;i<=m;++i) printf("%d\n",fc[a[i]][b[i]]);
}
