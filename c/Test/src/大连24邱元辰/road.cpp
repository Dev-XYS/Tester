#define yuki(x, y) for(int i = x, __yuki__ = y; i < __yuki__; ++i)
#define yukj(x, y) for(int j = x, __yukj__ = y; j < __yukj__; ++j)
#define yukii(x, y) for(int i = x, __yukii__ = y; i <= __yukii__; ++i)
#define yukji(x, y) for(int j = x, __yukji__ = y; j <= __yukji__; ++j)
#define yuk(x, y, z) for(int x = y, __yui__ = z; x < __yui__; ++x)
#define yui(x, y, z) for(int x = y, __yuk__ = z; x >= __yuk__; --x)
#define sclr(x) memset(x, 0, sizeof(x))
#define sclr1(x) memset(x, -1, sizeof(x))
#define scl(x, y) memset(x, y, sizeof(x))
#define ft first
#define sc second
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long lol;
typedef pair<lol, int> pii;
int n, m, A, tp, q, p[100100], head[100100], nxt[400100], tow[400100], dat[400100], alc,
    hea[100100], nx[400100], to[400100], da[400100], al, fa[100100], e[100100];
lol dis[100100];
bool vis[400100];
priority_queue<pii, vector<pii>, greater<pii> > pq;
void add(int s, int t, int w)
{
    nxt[++alc] = head[s];
    head[s] = alc;
    tow[alc] = t;
    dat[alc] = w;
}
void ad(int s, int t, int w)
{
    nx[++al] = hea[s];
    hea[s] = al;
    to[al] = t;
    da[al] = w;
}
void sread()
{
    scanf("%d%d%d%d", &n, &m, &A, &tp);
    yukii(1, n) scanf("%d", p+i);
    int s, t, w;
    yuki(0, m)
    {
        scanf("%d%d%d", &s, &t, &w);
        add(s, t, w);
        add(t, s, w);
    }
    scanf("%d", &q);
}
void pre()
{
    scl(dis, 0x7f);
    dis[A] = 0;
    pq.push(pii(0, A));
    while(!pq.empty())
    {
        int cur = pq.top().sc;
        pq.pop();
        if(vis[cur]) continue;
        vis[cur] = true;
        for(int i = head[cur];i;i = nxt[i])
            if(!vis[tow[i]] && dis[tow[i]] > dis[cur]+dat[i])
            {
                dis[tow[i]] = dis[cur]+dat[i];
                pq.push(pii(dis[tow[i]], tow[i]));
            }
    }
    yukii(1, n)
        for(int j = head[i];j;j = nxt[j])
            if(dis[tow[j]] == dis[i]+dat[j])
                ad(i, tow[j], dat[j]);
    vis[A] = false;
    int cnt = 1, cur = A;
    while(cnt < n)
    {
        int mip = 0;
        for(int i=  hea[cur];i;i = nx[i])
            if(vis[to[i]] && (!mip || p[to[i]] < p[to[mip]]))
                mip = i;
        if(!mip) {cur = fa[cur];continue;}
        e[to[mip]] = mip;
        mip = to[mip];
        fa[mip] = cur;
        vis[mip] = false;
        ++cnt;
        cur = mip;
    }
}
int Return(int u, int v, int a)
{
    for(int t = v; t != u; t = fa[t]) vis[e[t]] = false;
    return a;
}
bool dfs(int cur, int tar)
{
    if(cur == tar) return true;
    for(int i = hea[cur];i;i = nx[i])
        if(!vis[i] && dfs(to[i], tar)) return true;
    return false;
}
int ask(int u, int v)
{
    int cur = 0;
    for(int t = v; t != u; t = fa[t])
        vis[e[t]] = true, ++cur;
    for(int t = v; t != u; t = fa[t])
    {
        if(dfs(A, t)) return Return(u, t, cur);
        vis[e[t]] = false, --cur;
    }
    return 0;
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("road.in", "r", stdin);
    freopen("road.out", "w", stdout);
#endif // snowoi
    sread();
    pre();
    int la = 0, u, v;
    while(q--)
    {
        scanf("%d%d", &u, &v);
        if(tp) u ^= la, v ^= la;
        printf("%d\n", la = ask(u, v));
    }
	return 0;
}
