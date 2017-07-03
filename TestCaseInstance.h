#pragma once

#include "Checker.h"
#include "JudgingTimer.h"
#include "Process.h"
#include "SystemCommand.h"
#include "Utility.h"

#include <string>

using namespace std;

class TestCaseBriefResult
{
private:
	int _enum_TestCaseBriefResult;

public:
	static const int Unspecified = -1;
	static const int Accepted = 0;
	static const int WrongAnswer = 1;
	static const int RuntimeError = 2;
	static const int TimeLimitExceeded = 3;
	static const int MemoryLimitExceeded = 4;

	TestCaseBriefResult(int __enum_TestCaseBriefResult);
	
	bool operator == (int __cmp_TestCaseBriefResult);

	string ToString();
};

class TestCaseResult
{
private:
	TestCaseBriefResult _BriefResult;

public:
	TestCaseResult(TestCaseBriefResult __BriefResult);
	TestCaseResult(int __enum_BriefResult);

	string ToString();
};

class TestCaseInstance
{
private:
	SystemCommand _Executable;
	JudgingTimer _JudgingTimer;
	Checker _Checker;

	string _InputFile;
	string _OutputFile;
	string _AnswerFile;
	
	int _TimeLimit;
	int _MemoryLimit;

public:
	TestCaseInstance(SystemCommand __Executable, Checker __Checker, string __InputFile, string __OutputFile, string _AnswerFile, int __TimeLimit);
	
	TestCaseResult Test();
};
