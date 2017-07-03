#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char InputCommand[256], Command[256];
size_t CommandLength;

int main()
{
	printf("Tester Shell (c) 2017 Dev-XYS\n\n");
	while (1)
	{
		printf("Tester-Shell$ ");
		gets(InputCommand);
		if (strcmp(InputCommand, "exit") == 0)
		{
			break;
		}
		else
		{
			sprintf(Command, "./%s", InputCommand);
			system(Command);
		}
	}
	return 0;
}
