CC=gcc
CFLAGS= -pedantic -std=c89 -Wall

.PHONY: build run clean

all: build

build: ex

ex:
	$(CC) $(CFLAGS) HELLO.c -o ex

run: ex
	./ex

clean:
	rm -rf *.o *.txt ex