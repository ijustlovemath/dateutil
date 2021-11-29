default: all

CFLAGS = -g -Wall -pedantic

main.o: main.c
#	gcc -c main.c -o main.o

dateutil.o: dateutil.c
#	gcc ${CFLAGS} -c dateutil.c -o dateutil.o

all: dateutil.o main.o
	gcc -g dateutil.o main.o -o dateparse

test: all
	./dateparse
