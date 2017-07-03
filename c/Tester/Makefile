# Makefile of Project "Tester"

Objects = Checker.o Main.o Test.o Tester.o Timer.o

tester : $(Objects)
	gcc $(Objects) -O2 -o $@

copy : tester
	cp tester ../Invoker/

clean :
	rm $(Objects)
