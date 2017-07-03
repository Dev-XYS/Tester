#pragma once

#include "Process.h"

#include <cstdlib>

#include <string>

#include <unistd.h>

using namespace std;

class SystemCommand
{
public:
	string _CommandString;

public:
	SystemCommand(string __CommandString);
	
	int Run();
	pid_t RunInAnotherThread();
};
