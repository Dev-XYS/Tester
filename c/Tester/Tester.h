#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define TR_NONE 0
#define TR_AC 1
#define TR_WA 2
#define TR_RE 3
#define TR_TLE 4
#define TR_MLE 5

typedef unsigned int DWORD;

/* Global Variables */

extern char *CheckerCommand;
extern char ProcessKillCommand[];
extern int ReturnValue;
extern DWORD TestResult;
extern int TimeLimit;
extern int MemoryLimit;
extern int ProcessStatus;
extern struct rusage ProcessUsage;

/* Checker.c */

extern void Check();

/* Test.c */

extern void Test(DWORD TestType, char *Executable, char *ExecutableParameters, int TimeLimit, int MemoryLimit, char *CheckerCommand);
extern void WriteResultTo(char *ResultFile);

/* Timer.c */

extern void StartTimer();
extern void StopTimer();
