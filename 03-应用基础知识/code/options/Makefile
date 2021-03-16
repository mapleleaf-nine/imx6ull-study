#1
#testMakefile : main.c sub.c sub.h
#	gcc -o testMakefile main.c sub.c

#2
testMakefile : main.o sub.o
	gcc -o testMakefile main.o sub.o
main.o : main.c
	gcc -c -o main.o main.c
sub.o : sub.c
	gcc -c -o sub.o sub.c
clean : 
	rm testMakefile *.o -f