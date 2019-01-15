
test : test.o login.o
	gcc -o test test.o login.o

test.o : test.c 
	gcc -c test.c

login.o : login.c login.h util.o
	gcc -c login.c

util.o : util.c util.h
	gcc -c util.c

clean :
	rm test test.o login.o util.o

clean-o :
	rm test.o login.o util.o