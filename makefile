test: main.o proj.o
	gcc main.o proj.o -o test -g -lm

main.o: main.c proj.c proj.h
	gcc -Wall -c main.c -g

proj.o: proj.c proj.h
	gcc -Wall -c proj.c -g

clean: 
	rm *.o test
