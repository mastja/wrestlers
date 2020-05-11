# macro tells which compiler to use
CC = g++

# macro says using c++11 standard
CFLAGS = -std=c++11 -c

# run "make all" to run wrestlerRivalries
all: wrestlerRivalries

# make the wrestlerRivalries sort program
change: wrestlerRivalries.o
	$(CC) wrestlerRivalries.o -o wrestling

wrestlerRivalries.o:
	$(CC) $(CFLAGS) wrestlerRivalries.cpp


clean:
	rm *.o
	rm wrestlerRivalries