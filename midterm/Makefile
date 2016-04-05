all:midterm
clean:
	rm -f midterm.o midterm 
midterm.o:midterm.cpp
	g++ -c midterm.cpp -std=c++11 -o midterm.o
midterm:midterm.o
	g++ -s midterm.o -o midterm
