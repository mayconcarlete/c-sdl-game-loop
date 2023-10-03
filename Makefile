CC=gcc
CFLAGS= -g -w -Wall
INCLUDE= -I ./include

compile:
	$(CC) $(CFLAGS) $(INCLUDE) ./src/main.c -o ./bin/main

clean:
	rm -rf ./bin/*