#include "TestCaseInstance.h"

#include <sys/wait.h>

#include <iostream>

TestCaseBriefResult::TestCaseBriefResult(int __enum_TestCaseBriefResult) : _enum_TestCaseBriefResult(__enum_TestCaseBriefResult)
{
}

bool TestCaseBriefResult::operator == (int __cmp_TestCaseBriefResult)
{
	return _enum_TestCaseBriefResult == __cmp_TestCaseBriefResult;
}

string TestCaseBriefResult::ToString()
{
	switch (_enum_TestCaseBriefResult)
	{
	case TestCaseBriefResult::Unspecified:
		return "Unspecified";
	case TestCaseBriefResult::Accepted:
		return "Accepted";
	case TestCaseBriefResult::WrongAnswer:
		return "WrongAnswer";
	case TestCaseBriefResult::RuntimeError:
		return "RuntimeError";
	case TestCaseBriefResult::TimeLimitExceeded:
		return "TimeLimitExceeded";
	case TestCaseBriefResult::MemoryLimitExceeded:
		return "MemoryLimitExceeded";
	default:
		throw "Status caption not specified!";
	}
}

TestCaseResult::TestCaseResult(TestCaseBriefResult __BriefResult) : _BriefResult(__BriefResult)
{
}

TestCaseResult::TestCaseResult(int __enum_BriefResult) : _BriefResult(__enum_BriefResult)
{
}

string TestCaseResult::ToString()
{
	return _BriefResult.ToString();
}

TestCaseInstance::TestCaseInstance(SystemCommand __Executable, Checker __Checker, string __InputFile, string __OutputFile, string _AnswerFile, int __TimeLimit) : _Executable(__Executable), _JudgingTimer(__TimeLimit), _Checker(__Checker), _TimeLimit(__TimeLimit)
{
}

TestCaseResult TestCaseInstance::Test()
{
	pid_t pid = _Executable.RunInAnotherThread();
	_JudgingTimer.SetTimerTickCommand(SystemCommand(string("kill -9 ") + pid));
	_JudgingTimer.Start();
	wait(NULL);
	JudgingTimerResult timer_res = _JudgingTimer.Stop();
	if (timer_res == JudgingTimerResult::TimeLimitExceeded)
	{
		return TestCaseResult(TestCaseBriefResult::TimeLimitExceeded);
	}
	if (Process::LastReturnValue != 0)
	{
		return TestCaseResult(TestCaseBriefResult::RuntimeError);
	}
	CheckResult check_res = _Checker.Check();
	if (check_res == CheckResult::CorrectAnswer)
	{
		return TestCaseBriefResult::Accepted;
	}
	else
	{
		return TestCaseBriefResult::WrongAnswer;
	}
}
