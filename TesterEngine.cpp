#include "TesterEngine.h"

void TesterEngine::Test(Contestant __Contestant, Problem __Problem, TestCase __TestCase)
{
	StartTimer(__TestCase.TimeLimit);
	StartProgram(__Problem.ExecutableFile);
}
