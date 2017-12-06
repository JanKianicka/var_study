all:main other_small fork

main:setitimer_example.o
	cc -o main setitimer_example.o

setitimer_example.o: 
	cc -c -g setitimer_example.c
	
other_small:
	cc -o other_small other_small.c

fork:fork.o
	cc -o fork fork.o

fork.o:
	cc -c -g fork.c

clean:
	rm *.o main other_small fork