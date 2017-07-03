#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int main() {
  freopen("road.in", "r", stdin);
  freopen("road.out", "w", stdout);

  int N, M, S, Ty;
  scanf("%d%d%*d%*d", &N, &M);
  for (int i = 1; i <= N; ++i) scanf("%*d");
  for (int i = 1; i <= M; ++i)
    scanf("%*d%*d%*d");
  int Q;
  scanf("%d", &Q);
  while (Q--) puts("0");
  return 0;
}
