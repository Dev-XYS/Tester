#include "Tester.h"

struct itimerval TimerInfo;

void TimerTickProcedure(int TimerIdentifier)
{
	system(ProcessKillCommand);
	TestResult = TR_TLE;
}

void StartTimer()
{
	struct timeval value, interval;
	value.tv_sec = TimeLimit / 1000;
	value.tv_usec = TimeLimit % 1000 * 1000;
	interval.tv_sec = 0;
	interval.tv_usec = 0;
	TimerInfo.it_value = value;
	TimerInfo.it_interval = interval;
	signal(SIGALRM, TimerTickProcedure);
	setitimer(ITIMER_REAL, &TimerInfo, NULL);
}

void StopTimer()
{
	TimerInfo.it_value.tv_sec = 0;
	TimerInfo.it_value.tv_usec = 0;
}
