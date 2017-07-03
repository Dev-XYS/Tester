#include "Tester.h"

void Check()
{
	int CheckerReturnValue = system(CheckerCommand);
	if (CheckerReturnValue != 0)
	{
		TestResult = TR_WA;
	}
}
