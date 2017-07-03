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
int n, m, c, d, p, f[2][120][120][60], o;
bool obs[120][120];
int sp(int a, int b){return (a+b)%p;}
void sread()
{
    scanf("%d%d%d%d%d", &n, &m, &c, &d, &p);
    int x, y;
    sclr(obs);
    yuki(0, c)
    {
        scanf("%d%d", &x, &y);
        --x, --y;
        obs[x+y][x-y+m-1] = true;
    }
}
void mina()
{
    sread();
    sclr(f[o]);
    f[o][m-2][m][obs[1][m-2]+obs[1][m]] = 1;
    yuki(2, n+m-2)
    {
        o ^= 1;
        sclr(f[o]);
        yukj(max(i-m+1, 0), min(n-1, i))
            yuk(k, j+1, min(n, i+1))
                yuk(l, 0, d+1)
                {
                    int last = l, j1 = (j<<1)-i+m-1, j2 = (k<<1)-i+m-1;
                    last -= obs[i][j1] + obs[i][j2];
                    if(last < 0) continue;
                    f[o][j1][j2][l] = sp(j1 ? sp(f[o^1][j1-1][j2-1][last],
                                            f[o^1][j1-1][j2+1][last]) : 0,
                                         sp(f[o^1][j1+1][j2+1][last],
                                            j < k-1 ? f[o^1][j1+1][j2-1][last] : 0));
                }
    }
    int sum = 0;
    yukii(0, d) sum = sp(sum, f[o][n-2][n][i]);
    printf("%d\n", sum);
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("grid.in", "r", stdin);
    freopen("grid.out", "w", stdoout);
#endif // snowoi
    int t;
    for(scanf("%d", &t); t--; mina());
	return 0;
}
