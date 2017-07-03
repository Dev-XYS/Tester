#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
#define inf 1000000000000000000ll
#define inf2 1000000000
#define fi first
#define se second
#define mp(a,b) make_pair(a,b)
#define pb push_back
#define pa pair<int,int>
using namespace std;
int n,m,s,t,q,u[100010],v[100010],g[100010],h[100010],x[100010],y[100010],fa[100010],f[270000],p,r;
L w[100010];
vector<pa> a[100010],c;
vector<int> b[100010];
inline bool cmp(pa a,pa b)
{
    return u[a.fi]<u[b.fi];
}
inline bool cmp2(pa a,pa b)
{
    return h[a.se]<h[b.se];
}
inline void dfs(int i)
{
    int j,k;
    sort(&a[i][0],&a[i][0]+a[i].size(),cmp);
    v[i]=1;
    for(j=0;j<a[i].size();j++)
      if(!h[a[i][j].fi] && w[i]+a[i][j].se==w[k=a[i][j].fi])
        {
         b[i].pb(k);
         fa[k]=i;
         h[k]=h[i]+1;
         dfs(k);
         v[i]+=v[k];
        }
}
inline void slpf(int i,int l)
{
    int j,k;
    x[i]=++p;
    y[i]=l;
    if(!b[i].size())
      return;
    for(j=1,k=b[i][0];j<b[i].size();j++)
      if(v[b[i][j]]>v[k])
        k=b[i][j];
    slpf(k,l);
    for(j=0;j<b[i].size();j++)
      if(b[i][j]!=k)
        slpf(b[i][j],b[i][j]);
}
inline int lca(int i,int j)
{
    while(y[i]!=y[j])
      if(h[y[i]]>h[y[j]])
        i=fa[y[i]];
      else
        j=fa[y[j]];
    if(h[i]<h[j])
      return i;
    else
      return j;
}
inline void change(int i,int j,int k,int p,int x)
{
    if(j==k)
      f[i]=x;
    else
      {
       if(p<=(j+k>>1))
         change(i<<1,j,j+k>>1,p,x);
       else
         change(i<<1|1,(j+k>>1)+1,k,p,x);
       f[i]=min(f[i<<1],f[i<<1|1]);
      }
}
inline int ask(int i,int j,int k,int l,int r)
{
    if(l<=j && k<=r)
      return f[i];
    else
      {
       int w=inf2;
       if(l<=(j+k>>1))
         w=min(w,ask(i<<1,j,j+k>>1,l,r));
       if(r>(j+k>>1))
         w=min(w,ask(i<<1|1,(j+k>>1)+1,k,l,r));
       return w;
      }
}
inline int find(int i,int j,int k,int l,int r,int x)
{
    if(l<=j && k<=r)
      if(f[i]<=x)
        if(j==k)
          return j;
        else if(f[i<<1|1]<=x)
          return find(i<<1|1,(j+k>>1)+1,k,l,r,x);
        else
          return find(i<<1,j,j+k>>1,l,r,x);
      else
        return inf2;
    else
      {
       int w;
       if(r>(j+k>>1))
         {
          w=find(i<<1|1,(j+k>>1)+1,k,l,r,x);
          if(w<inf2)
            return w;
         }
       if(l<=(j+k>>1))
         w=find(i<<1,j,j+k>>1,l,r,x);
       return w;
      }
}
inline int ask(int i,int j)
{
    int k=inf2;
    while(h[y[i]]>h[j])
      {
       k=min(k,ask(1,1,p,x[y[i]],x[i]));
       i=fa[y[i]];
      }
    k=min(k,ask(1,1,p,x[i]-(h[i]-h[j]),x[i]));
    return k;
}
inline void line(int i,int j)
{
    int k=lca(i,j),l=ask(i,k);
    if(l<f[p+x[j]-1])
      change(1,1,p,x[j],l);
}
inline int find(int i,int j)
{
    int k;
    while(h[y[i]]>h[j])
      {
       k=find(1,1,p,x[y[i]],x[i],h[j]);
       if(k!=inf2)
         return h[i]-(x[i]-k);
       i=fa[y[i]];
      }
    k=find(1,1,p,x[i]-(h[i]-h[j]),x[i],h[j]);
    return h[i]-(x[i]-k);
}
int main()
{
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	int i,j,k,l;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(i=1;i<=n;i++)
	  scanf("%d",&u[i]);
	for(i=1;i<=m;i++)
	  {
       scanf("%d%d%d",&j,&k,&l);
       a[j].pb(mp(k,l));
       a[k].pb(mp(j,l));
      }
    for(i=1;i<=n;i++)
      w[i]=inf;
    w[s]=0;
    p=1;
    g[1]=s;
    h[s]=1;
    for(i=1;;i=i%n+1)
      {
       for(j=0;j<a[g[i]].size();j++)
         if(w[g[i]]+a[g[i]][j].se<w[k=a[g[i]][j].fi])
           {
            w[k]=w[g[i]]+a[g[i]][j].se;
            if(!h[k])
              {
               g[p=p%n+1]=k;
               h[k]=1;
              }
           }
       h[g[i]]=0;
       if(i==p)
         break;
      }
    h[s]=1;
    dfs(s);
    p=0;
    slpf(s,s);
    for(p=1;p<n;p<<=1);
    for(i=1;i<=n;i++)
      f[p+x[i]-1]=h[i];
    for(i=p+n;i<(p<<1);i++)
      f[i]=inf2;
    for(i=p-1;i>0;i--)
      f[i]=min(f[i<<1],f[i<<1|1]);
    for(i=1;i<=n;i++)
      for(j=0;j<a[i].size();j++)
        if(w[i]+a[i][j].se==w[a[i][j].fi] && fa[a[i][j].fi]!=i)
          c.pb(mp(i,a[i][j].fi));
    sort(&c[0],&c[0]+c.size(),cmp2);
    for(i=0;i<c.size();i++)
      line(c[i].fi,c[i].se);
    scanf("%d",&q);
    while(q--)
      {
       scanf("%d%d",&i,&j);
       if(t)
         {
          i^=r;
          j^=r;
         }
       r=find(j,i)-h[i];
       printf("%d\n",r);
      }
	return 0;
}

