CC = g++
LDFLAGS = -lncurses
CFLAGS = -std=c++11 -g

all: main

main: main.o cursestk.o MyWin.o
	${CC}  MyWin.o main.o cursestk.o ${LDFLAGS} -o main

main.o: main.cc cursestk.h MyWin.h
	${CC} ${CFLAGS} -c main.cc

cursestk.o: cursestk.h cursestk.cc
	${CC} ${CFLAGS} -c cursestk.cc

MyWin.o: MyWin.cc MyWin.h
	${CC}  ${CFLAGS} -c MyWin.cc

clean:
	rm main *.o
