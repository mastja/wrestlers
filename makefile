# macro tells which compiler to use
CC = g++

# macro says using c++11 standard
CFLAGS = -std=c++11 -c

# run "make all" to run wrestlerRivalries
all: wrestling

# make the wrestlerRivalries sort program
change: wrestling.o
	$(CC) wrestling.o

wrestling.o:
	$(CC) $(CFLAGS) wrestlerRivalries.cpp


clean:
	rm *.o
	rm wrestling