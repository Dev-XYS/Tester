#include <ctime>
#include <cstdio>
#include <cstring>
#include <algorithm>

const int M1 = 1e4;
const int M2 = 1e5;
const int M3 = 1e9;
int T, n, m, x, y;
char run[100];
char name[10] = "grid";
FILE *out;

int main() {
  for (int i = 1; i <= 20; ++i) {
    sprintf(run, "%s < %s%d.in > %s%d.ans", name, name, i, name, i);
    system(run);
  }
  return 0;
}
