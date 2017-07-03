#include "JudgingTimer.h"

#include <cstdio>
#include <iostream>

JudgingTimerResult::JudgingTimerResult(int __enum_JudgingTimerResult) : _enum_JudgingTimerResult(__enum_JudgingTimerResult)
{
}

bool JudgingTimerResult::operator == (int __cmp_JudgingTimerResult)
{
	return _enum_JudgingTimerResult == __cmp_JudgingTimerResult;
}

SystemCommand JudgingTimer::_static_TimerTickCommand("");
JudgingTimerResult JudgingTimer::_static_TimerResult = JudgingTimerResult::None;

void JudgingTimer::_sys_TimerTickProcedure(int __TimerIdentifier)
{
	_static_TimerTickCommand.Run();
	_static_TimerResult = JudgingTimerResult::TimeLimitExceeded;
}

JudgingTimer::JudgingTimer(int __TimeLimit) : _TimeLimit(__TimeLimit), _TimerTickCommand(""), _TimerResult(JudgingTimerResult::None)
{
}

void JudgingTimer::Start()
{
	timeval first_tick, interval;
	first_tick.tv_sec = _TimeLimit / 1000;
	first_tick.tv_usec = _TimeLimit % 1000 * 1000;
	interval.tv_sec = 0;
	interval.tv_usec = 0;
	_sys_TimerInfo.it_value = first_tick;
	_sys_TimerInfo.it_interval = interval;
	signal(SIGALRM, _sys_TimerTickProcedure);
	_static_TimerTickCommand = _TimerTickCommand;
	setitimer(ITIMER_REAL, &_sys_TimerInfo, NULL);
}

JudgingTimerResult JudgingTimer::Stop()
{
	_sys_TimerInfo.it_value.tv_sec = 0;
	_sys_TimerInfo.it_value.tv_usec = 0;
	_TimerResult = _static_TimerResult;
	return _TimerResult;
}

void JudgingTimer::SetTimerTickCommand(SystemCommand __TimerTickCommand)
{
	_TimerTickCommand = __TimerTickCommand;
}
