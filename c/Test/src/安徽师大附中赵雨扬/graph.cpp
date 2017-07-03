#include <cstdio>
#include <algorithm>
#include <ctime>

using namespace std;

typedef long long int64;

struct IO_Tp
{
	inline bool is_digit(char ch)
	{
		return '0' <= ch && ch <= '9';
	}
	
	inline int getop()
	{
		static char ch;
		while (ch = getchar(), ch != 'L' && ch != 'Q')
			;
		return ch;
	}
	
	inline IO_Tp& operator>>(int& buf)
	{
		buf = 0;
		static char ch;
		while (ch = getchar(), !is_digit(ch))
			;
		do
			(buf *= 10) += ch & 15;
		while (ch = getchar(), is_digit(ch));
		return *this;
	}
} IO;

const int Max_N(105), Max_M(2005);

int N, M, P;

int main(int argc, char** argv)
{
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
	
	IO >> N >> M >> P;
	
	int x[10], y[10], a[10], b[10];
	int x1[10], y1[10], a1[10], sa, sb;
	
	for (int i(0); i != M; ++i)
	{
		IO >> x[i] >> y[i] >> a[i] >> b[i];
		x1[i] = x[i], y1[i] = y[i], a1[i] = a[i];
	}
	
	if (y1[0] == y1[1])
		swap(x1[1], y1[1]), a1[1] = -a1[1];
	if (x1[0] == x1[1])
		swap(x1[0], y1[0]), a1[0] = -a1[0];
	if (x1[0] == y1[1])
		swap(x1[0], y1[0]), swap(x1[1], y1[1]), a1[0] = -a1[0], a1[1] = -a1[1];
	if (y1[1] == y1[2])
		swap(x1[2], y1[2]), a1[2] = -a1[2];
	
	sa = a1[0] + a1[1] + a1[2];
	sb = b[0] + b[1] + b[2];
	
	for (int i(0); i != P; ++i)
		if ((sb * i - sa) % P == 0)
		{
			printf("%d\n%d\n%d", x1[0] == x[0] ? i : P - i, x1[1] == x[1] ? i : P - i, x1[2] == x[2] ? i : P - i);
			return 0;
		}
}
