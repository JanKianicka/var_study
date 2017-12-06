all:printWrap.o printOrig.o
	cc -o main main.c printWrap.o printOrig.o

printWrap.o: 
	cc -c printWrap.c

printOrig.o:
	cc -c printOrig.c
	
printWrapSource.o:
	cc -c printWrapSource.c

clean:
	rm *.o main
