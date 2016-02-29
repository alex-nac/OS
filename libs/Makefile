all:main
clean:
	rm main hello1.o hello2.o main.o libhello1.a libhello2.so
main.o:main.c
	gcc -c main.c -o main.o
hello1.o:hello1.c
	gcc -c hello1.c -o hello1.o
hello2.o:hello2.c
	gcc -c -fPIC hello2.c -o hello2.o
libhello1.a:hello1.o
	ar rsc libhello1.a hello1.o
libhello2.so:hello2.o
	gcc -shared hello2.o -o libhello2.so
main:main.o libhello1.a libhello2.so
	gcc -s main.o -o main -L. -lhello1 -lhello2
	
