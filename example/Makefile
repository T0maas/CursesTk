CC = g++
LDFLAGS = -lncurses
CFLAGS = -std=c++11

all: main

main: main.o cursestk.o
	${CC}   main.o cursestk.o ${LDFLAGS} -o main

main.o: main.cc cursestk.h
	${CC} ${CFLAGS} -c main.cc

cursestk.o: cursestk.h cursestk.cc
	${CC} ${CFLAGS} -c cursestk.cc


