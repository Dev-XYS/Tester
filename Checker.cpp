#include "Checker.h"

CheckResult::CheckResult(int __enum_CheckResult) : _enum_CheckResult(__enum_CheckResult)
{
}

bool CheckResult::operator == (int __cmp_CheckResult)
{
	return _enum_CheckResult == __cmp_CheckResult;
}

Checker::Checker(string __CommandString, string __InputFile, string __OutputFile, string __AnswerFile, string __ResultFilePath) : _CheckCommand(__CommandString + ' ' + __InputFile + ' ' + __OutputFile + ' ' + __AnswerFile + ' ' + __ResultFilePath)
{
}

CheckResult Checker::Check()
{
	int checker_ret = _CheckCommand.Run();
	if (checker_ret == 0)
	{
		return CheckResult::CorrectAnswer;
	}
	else
	{
		return CheckResult::WrongAnswer;
	}
}
