server : server.o
	gcc -o server server.o

client : client.o
	gcc -o client client.o

test : test.o login.o
	gcc -o test test.o login.o

server.o : server.c
	gcc -c server.c

client.o : client.c
	gcc -c client.c 

test.o : test.c 
	gcc -c test.c

login.o : login.c login.h util.o
	gcc -c login.c

util.o : util.c util.h
	gcc -c util.c

clean :
	rm test server client server.o client.o test.o login.o util.o

clean-o :
	rm server.o client.o test.o login.o util.o