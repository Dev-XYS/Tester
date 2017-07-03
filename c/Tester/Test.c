#include "Tester.h"

void Test(DWORD TestType, char *Executable, char *ExecutableParameters, int _TimeLimit, int _MemoryLimit, char *_CheckerCommand)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		execlp(Executable, Executable, ExecutableParameters, NULL);
		printf("tester : execlp() failed.\n");
		exit(-1);
	}
	else
	{
		sprintf(ProcessKillCommand, "kill -9 %d", pid);
		TimeLimit = _TimeLimit;
		MemoryLimit = _MemoryLimit;
		StartTimer();
		wait4(pid, &ProcessStatus, __WALL, &ProcessUsage);
		StopTimer();
		if (TestResult == TR_TLE)
		{
			return;
		}
		if (ProcessUsage.ru_maxrss > MemoryLimit)
		{
			TestResult = TR_MLE;
			return;
		}
		if (ProcessStatus != 0)
		{
			TestResult = TR_RE;
			return;
		}
		CheckerCommand = _CheckerCommand;
		Check();
		if (TestResult == TR_WA)
		{
			return;
		}
		else
		{
			TestResult = TR_AC;
			return;
		}
	}
}

void WriteResultTo(char *ResultFile)
{
	struct rusage;
	freopen(ResultFile, "w", stdout);
	printf("TestResult: %u\n", TestResult);
	printf("TimeUsed: %d\n", ProcessUsage.ru_utime.tv_sec * 1000 + ProcessUsage.ru_utime.tv_usec / 1000);
	printf("MemoryUsed: %d\n", ProcessUsage.ru_maxrss);
}
