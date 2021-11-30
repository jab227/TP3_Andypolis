
CC = g++

CFLAGS  = -g -Wall -Werror -Wconversion

TARGET = main

NOMBRE = TP2

all: $(NOMBRE)

$(NOMBRE):  *.cpp Edificios/*.cpp Casillero/*.cpp
	$(CC) *.cpp Edificios/*.cpp Casillero/*.cpp $(CFLAGS) -o $(NOMBRE)
	
clean:
	$(RM) -v *.o
