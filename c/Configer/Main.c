#include <stdio.h>

char ConfigFileName[256];
int ProblemCount;
char ProblemName[256];
int Start;
int End;
int TimeLimit;
int MemoryLimit;
char AnswerFileSuffix[256];

void PromptTraditionalProblem()
{
	printf("ConfigFileName: ");
	scanf("%s", ConfigFileName);
	printf("ProblemCount: ");
	scanf("%d", &ProblemCount);

	FILE *ConfigFileDescriptor = fopen(ConfigFileName, "w");

	for (int p = 0; p < ProblemCount; p++)
	{
		printf("ProblemName: ");
		scanf("%s", ProblemName);
		printf("Start: ");
		scanf("%d", &Start);
		printf("End: ");
		scanf("%d", &End);
		printf("TimeLimit: ");
		scanf("%d", &TimeLimit);
		printf("MemoryLimit: ");
		scanf("%d", &MemoryLimit);
		printf("AnswerFileSuffix: ");
		scanf("%s", AnswerFileSuffix);

		fprintf(ConfigFileDescriptor, "echo\n");
		fprintf(ConfigFileDescriptor, "echo\n");
		fprintf(ConfigFileDescriptor, "echo%%20Problem:%%20%s\n", ProblemName);
		fprintf(ConfigFileDescriptor, "echo\n");
		fprintf(ConfigFileDescriptor, "rm%%20_tester_executable%%202>/dev/null\n");
		fprintf(ConfigFileDescriptor, "g++%%20src/$(CONTESTANT)/%s.cpp%%20-o_tester_executable_\n\n", ProblemName);
		fprintf(ConfigFileDescriptor, "#N0 %d\n\n", (End - Start + 1) * 3 + 1);
		fprintf(ConfigFileDescriptor, "echo\n");
	
		for (int i = Start; i <= End; i++)
		{
			char Config[1024];
			fprintf(ConfigFileDescriptor,
				"cp%%20data/%s/%s%d.in%%20%s.in\n\
#TC 0 ./_tester_executable_ >/dev/null%%202>/dev/null %d %d %d diff%%20%s.out%%20data/%s/%s%d%s%%20-w%%20>/dev/null%%202>/dev/null\n\
rm%%20%s.in%%20%s.out%%20>/dev/null%%202>/dev/null\n\n",
				ProblemName,
				ProblemName,
				i,
				ProblemName,
				i,
				TimeLimit,
				MemoryLimit,
				ProblemName,
				ProblemName,
				ProblemName,
				i,
				AnswerFileSuffix,
				ProblemName,
				ProblemName);
		}
		fprintf(ConfigFileDescriptor, "rm%%20_tester_executable_%%202>/dev/null\n\n");
	}
	fclose(ConfigFileDescriptor);
	printf("\n");
}

int main()
{
	printf("Configer (c) 2017 Dev-XYS\n\n");
	PromptTraditionalProblem();
	return 0;
}
