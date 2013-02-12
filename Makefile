myshell: support.o shell.o
	gcc -o myshell support.o shell.o
support.o: support.c support.h
	gcc -c support.c
shell.o: shell.c support.h
	gcc -c shell.c
clean:
	\rm *.o myshell