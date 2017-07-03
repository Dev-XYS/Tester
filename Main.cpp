#include "TestCaseInstance.h"

#include <iostream>

using namespace std;

int main()
{
	TestCaseInstance TCI(SystemCommand("./_tester_exe_ 2>/dev/null"), Checker("diff t.out t.ans"), 1000);
	cout << "Result = " << TCI.Test().ToString() << endl;
	return 0;
}
