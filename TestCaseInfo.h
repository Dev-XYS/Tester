#include "TestCaseInstance.h"

#include <string>

using namespace std;

class TestCaseInfo
{
private:
	string _TestCaseName;
	string _InputFileName;
	string _OutputFileName;
	string _AnswerFilename;

	int _TimeLimit;
	int _MemoryLimit;

public:
	TestCaseResult Test();
};
