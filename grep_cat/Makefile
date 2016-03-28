all:grep_cat
clean:
	rm -f grep_cat.o grep_cat 
grep_cat.o:grep_cat.c
	gcc -c grep_cat.c -o grep_cat.o
grep_cat:grep_cat.o
	gcc -s grep_cat.o -o grep_cat
