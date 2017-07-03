# Makefile of Project "Tester"

Objects = Main.o TestCaseInstance.o JudgingTimer.o SystemCommand.o Checker.o Process.o Utility.o

tester : $(Objects)
	g++ $(Objects) -Wall -Weffc++ -o $@

clean :
	rm *.o
