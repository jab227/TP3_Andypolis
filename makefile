
CC = g++

CFLAGS  = -g -Wall -Werror -Wconversion

TARGET = main

NOMBRE = TP3

all: $(NOMBRE)

$(NOMBRE):  *.cpp edificio/*.cpp edificio/edificios/*.cpp Casillero/*.cpp Casillero/casilleros/*.cpp empresa/*.cpp programa/*.cpp material/*.cpp utils/*.cpp printer/*.cpp jugador/*.cpp jugador/jugadores/*.cpp meta/*.cpp meta/objetivos/*.cpp meta/objetivos/tipos/*.cpp parser/parser_edificio.cpp 
	$(CC) *.cpp edificio/*.cpp edificio/edificios/*.cpp Casillero/*.cpp Casillero/casilleros/*.cpp empresa/*.cpp programa/*.cpp material/*.cpp utils/*.cpp printer/*.cpp jugador/*.cpp jugador/jugadores/*.cpp meta/*.cpp meta/objetivos/*.cpp meta/objetivos/tipos/*.cpp  parser/parser_edificio.cpp $(CFLAGS) -o $(NOMBRE)

clean:
	$(RM) -v *.o
