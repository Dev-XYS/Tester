#include <cstdio>

using namespace std;

int n, m, P, U[2010], V[2010], A[105][105], B[105][105], C[105][105];

bool check()
{
	if ((C[1][2] + C[1][3]) % 5 != 0) return false;
	if ((C[2][1] + C[2][3]) % 5 != 0) return false;
	if ((C[3][1] + C[3][2]) % 5 != 0) return false;
	if ((B[1][2] * C[1][2] + B[2][3] * C[2][3] + B[3][1] * C[3][1]) % 5 != (A[1][2] + A[2][3] + A[3][1]) % 5) return false;
	return true;
}

void printc()
{
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &P);
	int a, b;
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d%d", &U[i], &V[i], &a, &b);
		A[U[i]][V[i]] = a;
		A[V[i]][U[i]] = (P - a) % P;
		B[U[i]][V[i]] = b;
		B[V[i]][U[i]] = b;
	}
	for (int i = 0; i < 5; i++)
	{
		C[U[0]][V[0]] = i;
		C[V[0]][U[0]] = (5 - i) % 5;
		for (int j = 0; j < 5; j++)
		{
			C[U[1]][V[1]] = j;
			C[V[1]][U[1]] = (5 - j) % 5;
			for (int k = 0; k < 5; k++)
			{
				C[U[2]][V[2]] = k;
				C[V[2]][U[2]] = (5 - k) % 5;
				if (check() == true)
				{
					printf("%d\n%d\n%d\n", i, j, k);
					return 0;
				}
			}
		}
	}
	return 0;
}
