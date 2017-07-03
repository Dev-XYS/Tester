class TesterEngine
{
private:
	Contestant _Contestant;
	Problem _Problem;
	TestCase _TestCase;
	
public:
	void TestEngine(Contestant __Contestant, Problem __Problem, Testcase __TestCase);
	TestCaseResult Test();
};
