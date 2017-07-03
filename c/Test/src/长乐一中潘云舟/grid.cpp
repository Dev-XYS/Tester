#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

inline int getint()
{
	static char c;
	while ((c = getchar()) < '0' || c > '9');

	int res = c - '0';
	while ((c = getchar()) >= '0' && c <= '9')
		res = res * 10 + c - '0';
	return res;
}

int main()
{
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);



	fclose(stdin);
	fclose(stdout);
	return 0;
}