all:sigusr
clean:
	rm -f sigusr.o sigusr
sigusr:sigusr.o
	gcc -s sigusr.o -o sigusr
sigusr.o:sigusr.c
	gcc -c sigusr.c -Wall -o sigusr.o
