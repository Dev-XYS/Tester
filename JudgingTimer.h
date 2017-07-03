#pragma once

#include "SystemCommand.h"

#include <sys/signal.h>
#include <sys/time.h>

class JudgingTimerResult
{
private:
	int _enum_JudgingTimerResult;

public:
	static const int None = 0;
	static const int TimeLimitExceeded = 1;

	JudgingTimerResult(int __enum_JudgingTimerResult);

	bool operator == (int __cmp_JudgingTimerResult);
};

class JudgingTimer
{
private:
	int _TimeLimit;
	int _Duration;
	SystemCommand _TimerTickCommand;
	JudgingTimerResult _TimerResult;

	static SystemCommand _static_TimerTickCommand;
	static JudgingTimerResult _static_TimerResult;

	itimerval _sys_TimerInfo;
	
	static void _sys_TimerTickProcedure(int __TimerIdentifier);

public:
	JudgingTimer(int __TimeLimit);
	
	void Start();
	JudgingTimerResult Stop();
	void SetTimerTickCommand(SystemCommand __TimerTickCommand);
};
