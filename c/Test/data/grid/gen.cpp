#include <map>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define mp std::make_pair

const int M1 = 1e6;
const int M2 = 5e8;
int n, m, C, D;
char input[100];
char name[20] = "grid";
FILE *out;
int p1[20] = {949687, 904207, 219953, 533837, 503017, 346441, 621799, 867161, 867857, 135271,
             760007, 159319, 521999, 801733, 161869, 224677, 766477, 549767, 439493, 377831};
int p2[20] = {157208617, 212980907, 995569021, 785039743, 329156579, 272854481, 114027131, 945702907, 113629981, 987476309,
              244893853, 354395357, 637371001, 892580981, 540873449, 215174621, 142479509, 767789453, 189659231, 531481393};
std::map<std::pair<int, int>, bool> bo;

inline int Rand() {
  return (rand() << 15) | rand();
}

inline long long RAND() {
  long long x = rand();
  x = (x << 15) | rand();
  x = (x << 15) | rand();
  x = (x << 15) | rand();
  return x;
}

int Range(int a, int b) {
  return a + Rand() % (b - a + 1);
}

void gen1(int number) {
  sprintf(input, "%s%d.in", name, number);
  out = fopen(input, "w");

  if (number & 1) std::random_shuffle(p1, p1 + 20); 
  
  fprintf(out, "%d\n", 5);
  for (int tt = 1; tt <= 5; ++tt) {
    n = 2 + rand() % 4;
    m = 2 + rand() % 4;
    C = 2 + rand() % std::max(1, (n * m - 3) * 2 / 3);
    D = 2 + rand() % (C - 1);
    if (number & 1) fprintf(out, "%d %d %d %d %d\n", n, m, C, D, p1[tt]);
    else fprintf(out, "%d %d %d %d %d\n", n, m, C, D, 100000 + Rand() % M1 + 1);

    bo.clear();
    bo[mp(1, 1)] = bo[mp(n, m)] = true;
    for (int i = 1; i <= C; ++i) {
      int x, y;
      do {
        x = Rand() % n + 1;
        y = Rand() % m + 1;
      } while (bo[mp(x, y)]);
      bo[mp(x, y)] = true;
      fprintf(out, "%d %d\n", x, y);
    }
  }
}

void gen2(int number) {
  sprintf(input, "%s%d.in", name, number);
  out = fopen(input, "w");
  
  if (number & 1) std::random_shuffle(p1, p1 + 20); 
  
  fprintf(out, "%d\n", 5);
  for (int tt = 1; tt <= 5; ++tt) {
    n = 40 + rand() % 11;
    m = 40 + rand() % 11; 
    C = 10 + rand() % 41;
    D = 2 + rand() % (C * 2 / 3);
    if (number & 1) fprintf(out, "%d %d %d %d %d\n", n, m, C, D, p1[tt]);
    else fprintf(out, "%d %d %d %d %d\n", n, m, C, D, 100000 + Rand() % M1 + 1);

    bo.clear();
    bo[mp(1, 1)] = bo[mp(n, m)] = true;
    for (int i = 1; i <= C; ++i) {
      int x, y;
      do {
        x = Rand() % n + 1;
        y = Rand() % m + 1;
      } while (bo[mp(x, y)]);
      bo[mp(x, y)] = true;
      fprintf(out, "%d %d\n", x, y);
    }
  }
}

void gen3(int number) {
  sprintf(input, "%s%d.in", name, number);
  out = fopen(input, "w");
  
  if (number & 1) std::random_shuffle(p2, p2 + 20); 
  
  fprintf(out, "%d\n", 5);
  for (int tt = 0; tt <= 4; ++tt) {
    n = 100000 - tt * 5000 - rand(); 
    m = 100000 - tt * 5000 - rand();  
    C = 0;
    D = 0;
    if (number & 1) fprintf(out, "%d %d %d %d %d\n", n, m, C, D, p2[tt]);
    else fprintf(out, "%d %d %d %d %d\n", n, m, C, D, 500000000 + Rand() % M2);

    bo.clear();
    bo[mp(1, 1)] = bo[mp(n, m)] = true;
    for (int i = 1; i <= C; ++i) {
      int x, y;
      do {
        x = Rand() % n + 1;
        y = Rand() % m + 1;
      } while (bo[mp(x, y)]);
      bo[mp(x, y)] = true;
      fprintf(out, "%d %d\n", x, y);
    }
  }
}

void gen4(int number) {
  sprintf(input, "%s%d.in", name, number);
  out = fopen(input, "w");
  
  if (number & 1) std::random_shuffle(p2, p2 + 20); 
  
  fprintf(out, "%d\n", 5);
  for (int tt = 0; tt <= 4; ++tt) {
    n = 100000 - tt * 5000 - rand(); 
    m = 100000 - tt * 5000 - rand();  
    C = 150 + rand() % 51;
    D = 0;
    if (number & 1) fprintf(out, "%d %d %d %d %d\n", n, m, C, D, p2[tt]);
    else fprintf(out, "%d %d %d %d %d\n", n, m, C, D, 500000000 + Rand() % M2);
    bo.clear();
    bo[mp(1, 1)] = bo[mp(n, m)] = true;
    for (int i = 1; i <= C; ++i) {
      int x, y;
      do {
        x = Rand() % n + 1;
        y = Rand() % m + 1;
      } while (bo[mp(x, y)]);
      bo[mp(x, y)] = true;
      fprintf(out, "%d %d\n", x, y);
    }
  }
}

void gen5(int number) {
  sprintf(input, "%s%d.in", name, number);
  out = fopen(input, "w");
  
  if (number & 1) std::random_shuffle(p2, p2 + 20); 
  
  fprintf(out, "%d\n", 5);
  for (int tt = 0; tt <= 4; ++tt) {
    n = 100000 - tt * 5000 - rand(); 
    m = 100000 - tt * 5000 - rand();  
    C = 180 + rand() % 21;
    D = Range(0.2 * tt * C, 0.2 * (tt + 1) * C);
    if (number & 1) fprintf(out, "%d %d %d %d %d\n", n, m, C, D, p2[tt]);
    else fprintf(out, "%d %d %d %d %d\n", n, m, C, D, 500000000 + Rand() % M2);
    bo.clear();
    bo[mp(1, 1)] = bo[mp(n, m)] = true;
    for (int i = 1; i <= C; ++i) {
      int x, y;
      do {
        x = Rand() % n + 1;
        y = Rand() % m + 1;
      } while (bo[mp(x, y)]);
      bo[mp(x, y)] = true;
      fprintf(out, "%d %d\n", x, y);
    }
  }
}

int main() {
  srand((unsigned)time(NULL));
  for (int i = 1; i <= 4; ++i) gen1(i);
  for (int i = 5; i <= 8; ++i) gen2(i);
  for (int i = 9; i <= 12; ++i) gen3(i);
  for (int i = 13; i <= 16; ++i) gen4(i);
  for (int i = 17; i <= 20; ++i) gen5(i);
  return 0;
}
