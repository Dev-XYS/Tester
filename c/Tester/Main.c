#include "Tester.h"

#include <stdlib.h>

int main(int argc, char **argv)
{
	Test(atoi(argv[1]),
	     argv[2],
	     argv[3],
	     atoi(argv[4]),
	     atoi(argv[5]),
	     argv[6]);
	WriteResultTo(argv[7]);
	return 0;
}
