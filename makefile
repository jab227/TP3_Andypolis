
CC = g++

CFLAGS  = -g -Wall -Werror -Wconversion

TARGET = main

NOMBRE = TP3

all: $(NOMBRE)

$(NOMBRE):  *.cpp edificio/*.cpp edificio/edificios/*.cpp Casillero/*.cpp  Casillero/casilleros/*.cpp empresa/*.cpp programa/*.cpp material/*.cpp utils/*.cpp printer/*.cpp jugador/*.cpp jugador/jugadores/*.cpp objetivos/*.cpp objetivos/tipos/*.cpp  
	$(CC) *.cpp edificio/*.cpp edificio/edificios/*.cpp Casillero/*.cpp  Casillero/casilleros/*.cpp empresa/*.cpp programa/*.cpp material/*.cpp utils/*.cpp printer/*.cpp jugador/*.cpp jugador/jugadores/*.cpp objetivos/*.cpp objetivos/tipos/*.cpp  $(CFLAGS) -o $(NOMBRE)

test_material:  test/test_material/*.cpp material/*.cpp 
	$(CC)  test/test_material/*.cpp material/*.cpp  $(CFLAGS) -o test

test_edificios: test/test_edificio/*.cpp edificio/*.cpp edificio/edificios/*.cpp material/*.cpp 
	$(CC) test/test_edificio/*.cpp edificio/*.cpp edificio/edificios/*.cpp material/*.cpp  $(CFLAGS) -o test

test_coordenada: test/test_coordenada/*.cpp utils/coordenada.cpp 
	$(CC) test/test_coordenada/*.cpp utils/coordenada.cpp  $(CFLAGS) -o test

test_casillero: test/test_casilleros/*.cpp edificio/edificios/*.cpp material/*.cpp Casillero/*.cpp Casillero/casilleros/*.cpp utils/*.cpp edificio/*.cpp empresa/Almacen.cpp
	$(CC) test/test_casilleros/*.cpp edificio/edificios/*.cpp material/*.cpp Casillero/*.cpp Casillero/casilleros/*.cpp utils/*.cpp edificio/*.cpp empresa/Almacen.cpp $(CFLAGS) -o test

test_jugador: test/test_jugador/*.cpp edificio/edificios/*.cpp material/*.cpp Casillero/*.cpp Casillero/casilleros/*.cpp utils/*.cpp edificio/*.cpp empresa/Almacen.cpp
	$(CC) test/test_jugador/*.cpp edificio/edificios/*.cpp material/*.cpp Casillero/*.cpp Casillero/casilleros/*.cpp utils/*.cpp edificio/*.cpp empresa/Almacen.cpp $(CFLAGS) -o test

test_objetivos: test/test_objetivo/*.cpp material/*.cpp  edificio/*.cpp  edificio/edificios/*.cpp  utils/*.cpp empresa/Almacen.cpp
	$(CC) test/test_objetivo/*.cpp  material/*.cpp Casillero/*.cpp  edificio/*.cpp edificio/edificios/*.cpp utils/*.cpp empresa/Almacen.cpp $(CFLAGS) -o test

clean:
	$(RM) -v *.o
