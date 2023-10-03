CC=gcc
CFLAGS= -g -w -Wall
INCLUDE= -I ./include

compile:
	$(CC) $(CFLAGS) $(INCLUDE) ./src/main.c -L ./lib -lSDL2main -lSDL2 -o ./bin/main

run:
	./bin/main

clean:
	rm -rf ./bin/*