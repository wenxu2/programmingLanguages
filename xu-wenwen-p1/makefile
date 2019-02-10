test: main.o proj.o symbol.o
	gcc main.o proj.o symbol.o -o test -g -lm

main.o: main.c proj.c proj.h symbol.c symbol.h
	gcc -Wall -c main.c -g

proj.o: proj.c proj.h symbol.c symbol.h
	gcc -Wall -c proj.c -g

symbol.o: symbol.c symbol.h
	gcc -Wall -c symbol.c -g

clean: 
	rm *.o test
