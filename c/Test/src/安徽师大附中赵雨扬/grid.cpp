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

const int Max_N(100005);

int T, N, M, C, D, Ans, Mod, R[55][55], F[105][55][55][55];

int main(int argc, char** argv)
{
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	
	IO >> T;
	while (T--)
	{
		IO >> N >> M >> C >> D >> Mod;
		for (int i(1); i <= N; ++i)
			for (int j(1); j <= M; ++j)
				R[i][j] = 0; 
		for (int i(1), x, y; i <= C; ++i)
			IO >> x >> y, R[x][y] = 1;
		Ans = 0;
		for (int t(0); t <= N + M; ++t)
			for (int x1(0); x1 <= N; ++x1)
				for (int x2(x1); x2 <= N; ++x2)
					for (int d(0); d <= D; ++d)
						F[t][x1][x2][d] = 0;
		
		F[2][1][1][0] = 1;
		for (int t(3); t <= N + M; ++t)
			for (int x1(1); x1 <= N; ++x1)
				for (int x2((t == N + M && x1 == N) ? x1 : x1 + 1); x2 <= N; ++x2)
				{
					int y1(t - x1), y2(t - x2), delta(R[x1][y1] + R[x2][y2]);
					for (int d(delta); d <= D; ++d)
						F[t][x1][x2][d] = ((F[t - 1][x1 - 1][x2 - 1][d - delta] + F[t - 1][x1 - 1][x2][d - delta]) % Mod + (F[t - 1][x1][x2 - 1][d - delta] + F[t - 1][x1][x2][d - delta]) % Mod) % Mod;
				}
		
		for (int d(0); d <= D; ++d)
			(Ans += F[N + M][N][N][d]) %= Mod;
		printf("%d\n", Ans);
	}
	
	return 0;
}
