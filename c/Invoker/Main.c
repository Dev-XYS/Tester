#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define TR_NONE 0
#define TR_AC 1
#define TR_WA 2
#define TR_RE 3
#define TR_TLE 4
#define TR_MLE 5

#define RED(...) "\033[31m"__VA_ARGS__"\033[0m"
#define GREEN(...) "\033[32m"__VA_ARGS__"\033[0m"
#define YELLOW(...) "\033[33m"__VA_ARGS__"\033[0m"
#define MAGENTA(...) "\033[35m"__VA_ARGS__"\033[0m"

typedef int BOOL;

struct ConfigElement
{
	char MainCommand[256];
	int TestType;
	char Identifier[256];
	char Executable[256];
	char ExecutableParameters[256];
	int TimeLimit;
	int MemoryLimit;
	char CheckerCommand[256];
	char OutputFile[256];
	char AnswerFile[256];
	char Parameter[256];
}Config[1000];

int CommandCount;
BOOL IsContestantSelected;
char SelectedContestant[256];

BOOL strstt(char *String1, char *String2)
{
	if (strlen(String1) < strlen(String2))
	{
		return FALSE;
	}
	else
	{
		size_t Length = strlen(String2);
		for (int i = 0; i < Length; i++)
		{
			if (String1[i] != String2[i])
			{
				return FALSE;
			}
		}
		return TRUE;
	}
}

void strrpl(char *Destination, char *Source, char *Pattern, char *ReplaceString)
{
	size_t SourceLength = strlen(Source);
	size_t PatternLength = strlen(Pattern);
	size_t ReplaceStringLength = strlen(ReplaceString);
	size_t DestinationPointer = 0;
	for (int i = 0; i < SourceLength; )
	{
		for (int j = 0; j < PatternLength; j++)
		{
			if (Source[i + j] != Pattern[j])
			{
				goto NEXT_POSITION;
			}
		}
		strcpy(Destination + DestinationPointer, ReplaceString);
		DestinationPointer += ReplaceStringLength;
		i += PatternLength;
		continue;
	NEXT_POSITION:
		Destination[DestinationPointer++] = Source[i];
		i++;
	}
	Destination[DestinationPointer] = 0;
}

void LoadConfig(char *ConfigFile)
{
	CommandCount = 0;
	FILE *ConfigFileDescriptor = fopen(ConfigFile, "r");
	while (fscanf(ConfigFileDescriptor, "%s", Config[CommandCount].MainCommand) > 0)
	{
		if (strcmp(Config[CommandCount].MainCommand, "#TC") == 0)
		{
			fscanf(ConfigFileDescriptor, "%d%s%s%s%d%d%s",
			       &Config[CommandCount].TestType,
			       Config[CommandCount].Executable,
			       Config[CommandCount].ExecutableParameters,
			       Config[CommandCount].Identifier,
			       &Config[CommandCount].TimeLimit,
			       &Config[CommandCount].MemoryLimit,
			       Config[CommandCount].CheckerCommand/*,
			       Config[CommandCount].OutputFile,
			       Config[CommandCount].AnswerFile*/);
		}
		else if (strcmp(Config[CommandCount].MainCommand, "#N0") == 0)
		{
			fscanf(ConfigFileDescriptor, "%s",
			       Config[CommandCount].Parameter);
		}
		CommandCount++;
	}
	fclose(ConfigFileDescriptor);
}

void PrintPrompt(char *Identifier)
{
	printf("Test for Testcase #%3s  ", Identifier);
}

void PrintResult()
{
	FILE *ResultFileDescriptor = fopen("RESULT", "r");
	if (ResultFileDescriptor == NULL)
	{
		printf("JF\n");
		return;
	}
	char Temp[256];
	int BriefResult;
	int TimeUsed;
	int MemoryUsed;
	fscanf(ResultFileDescriptor, "%s%d%s%d%s%d", Temp, &BriefResult, Temp, &TimeUsed, Temp, &MemoryUsed);
	fclose(ResultFileDescriptor);
	switch (BriefResult)
	{
	case TR_AC:
		printf(GREEN(" AC"));
		break;
	case TR_WA:
		printf(RED(" WA"));
		break;
	case TR_RE:
		printf(YELLOW(" RE"));
		break;
	case TR_TLE:
		printf(RED("TLE"));
		break;
	case TR_MLE:
		printf(RED("MLE"));
		break;
	default:
		printf("---");
	}
	if (BriefResult == TR_TLE)
	{
		printf("         %8dKB\n", MemoryUsed);
	}
	else
	{
		printf("%6dms %8dKB\n", TimeUsed, MemoryUsed);
	}
}

void TestContestant(char *ContestantName)
{
	printf("\n>>> Contestant : %s\n", ContestantName);
	char TesterCommand[1024];
	int LastReturnValue = 0;
	for (int i = 0; i < CommandCount; i++)
	{
		if (strcmp(Config[i].MainCommand, "#TC") == 0)
		{
			char sExecutable[256], Executable[256];
			char sExecutableParameters[256], ExecutableParameters[256];			char sCheckerCommand[256], CheckerCommand[256];
			strrpl(sExecutable, Config[i].Executable, "$(CONTESTANT)", ContestantName);
			strrpl(Executable, sExecutable, "%20", " ");
			strrpl(sExecutableParameters, Config[i].ExecutableParameters, "$(CONTESTANT)", ContestantName);
			strrpl(ExecutableParameters, sExecutableParameters, "%20", " ");
			strrpl(sCheckerCommand, Config[i].CheckerCommand, "$(CONTESTANT)", ContestantName);
			strrpl(CheckerCommand, sCheckerCommand, "%20", " ");
			PrintPrompt(Config[i].Identifier);
			char TesterCommand[1024];
			sprintf(TesterCommand, "./tester %d \"%s\" \"%s\" %d %d \"%s\" RESULT",
				Config[i].TestType,
				Executable,
				ExecutableParameters,
				Config[i].TimeLimit,
				Config[i].MemoryLimit,
				CheckerCommand/*,
				Config[i].OutputFile,
				Config[i].AnswerFile*/);
			LastReturnValue = system(TesterCommand);
			PrintResult();
		}
		else if (strcmp(Config[i].MainCommand, "#N0") == 0)
		{
			if (LastReturnValue != 0)
			{
				i += atoi(Config[i].Parameter);
			}
		}
		else
		{
			char ParsedContestantCommand[1024];
			char ParsedSpaceCommand[1024];
			strrpl(ParsedContestantCommand, Config[i].MainCommand, "$(CONTESTANT)", ContestantName);
			strrpl(ParsedSpaceCommand, ParsedContestantCommand, "%20", " ");
			LastReturnValue = system(ParsedSpaceCommand);
		}
	}
	printf("\n");
}

void TestAllContestant()
{
	system("ls src/ > _tester_contestant_list_");
	FILE *ListDescriptor = fopen("_tester_contestant_list_", "r");
	char ContestantName[256];
	while (fscanf(ListDescriptor, "%s", ContestantName) > 0)
	{
		TestContestant(ContestantName);
	}
}

int main()
{
	printf("Invoker (c) 2017 Dev-XYS\n\n");
	char InputCommand[256];
	while (1)
	{
		if (IsContestantSelected)
		{
			printf("Invoker@%s$ ", SelectedContestant);
		}
		else
		{
			printf("Invoker$ ");
		}
		gets(InputCommand);
		if (strcmp(InputCommand, "exit") == 0)
		{
			break;
		}
		else if (strstt(InputCommand, "load "))
		{
			char ConfigFile[256];
			strcpy(ConfigFile, InputCommand + 5);
			LoadConfig(ConfigFile);
		}
		else if (strcmp(InputCommand, "cc") == 0)
		{
			IsContestantSelected = FALSE;
		}
		else if (strstt(InputCommand, "cc "))
		{
			strcpy(SelectedContestant, InputCommand + 3);
			IsContestantSelected = TRUE;
		}
		else if (strcmp(InputCommand, "test") == 0)
		{
			if (IsContestantSelected)
			{
				TestContestant(SelectedContestant);
			}
			else
			{
				TestAllContestant();
			}
		}
		else
		{
			printf("Command not found.\n");
		}
	}
	return 0;
}
