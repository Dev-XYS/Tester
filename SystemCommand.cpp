#include "SystemCommand.h"

#include <iostream>

SystemCommand::SystemCommand(string __CommandString) : _CommandString(__CommandString)
{
}

int SystemCommand::Run()
{
	return system(_CommandString.c_str());
}

pid_t SystemCommand::RunInAnotherThread()
{
	pid_t fork_ret = fork();
	if (fork_ret == 0)
	{
		Process::LastReturnValue = Run();
		exit(Process::LastReturnValue);
	}
	if (fork_ret == -1)
	{
		throw "fork() failed.";
	}
	return fork_ret;
}
