
CC = g++

CFLAGS  = -g -Wall -Werror -Wconversion

TARGET = main

NOMBRE = TP2

all: $(NOMBRE)

$(NOMBRE):  *.cpp edificio/*.cpp edificio/edificios/*.cpp Casillero/*.cpp empresa/*.cpp programa/*.cpp material/*.cpp utils/*.cpp jugador/*.cpp jugador/jugadores/*.cpp
	$(CC) *.cpp edificio/*.cpp edificio/edificios/*.cpp Casillero/*.cpp empresa/*.cpp programa/*.cpp material/*.cpp utils/*.cpp jugador/*.cpp jugador/jugadores/*.cpp $(CFLAGS) -o $(NOMBRE)
	
clean:
	$(RM) -v *.o
