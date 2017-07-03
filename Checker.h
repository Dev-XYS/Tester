#pragma once

#include "SystemCommand.h"

#include <string>

class CheckResult
{
private:
	int _enum_CheckResult;
	
public:
	static const int CorrectAnswer = 0;
	static const int WrongAnswer = 1;

	CheckResult(int __enum_CheckResult);
	
	bool operator == (int __cmp_CheckResult);
};

class Checker
{
private:
	SystemCommand _CheckCommand;

public:
	Checker(string __CommandString, string __InputFile, string __OutputFile, string __AnswerFile, string __ResultFilePath);

	CheckResult Check();
};
