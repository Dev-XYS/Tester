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
using namespace std;
typedef long long lol;
int n, m, p, in[3], a, b;
int enc(int s, int t)
{
    if(s == 1 && t == 2) return 0;
    if(s == 2 && t == 3) return 1;
    return 2;
}
int ksm(int a, int b)
{
    if(!b) return 1;
    int t = ksm(a, b>>1);
    t = t*t%p;
    if(b & 1) t = t*a%p;
    return t;
}
void sread()
{
    scanf("%d%d%d", &n, &m, &p);
    int s, t, ta, tb;
    yuki(0, m)
    {
        scanf("%d%d%d%d", &s, &t, &ta, &tb);
        if(!(s == 3 && t == 1) && (s > t || (s == 1 && t == 3)))
        {
            swap(s, t);
            ta = p-ta;
            in[enc(s, t)] = -1;
        }
        int id = enc(s, t);
        if(!in[id]) in[id] = 1;
        a += ta, b += tb;
    }
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
#endif // snowoi
    sread();
    int c = a*ksm(b, p-2)%p;
    yuki(0, m)
        printf("%d\n", (p+c*in[i])%p);
	return 0;
}
