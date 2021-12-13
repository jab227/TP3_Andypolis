
CXX = g++

# -g es debug, -O optimizado, para un build final
CXXFLAGS = -O2 -Wall -Werror -Wconversion

TARGET = main

NOMBRE = TP3

all: $(NOMBRE)

$(NOMBRE):  *.cpp edificio/*.cpp edificio/edificios/*.cpp Casillero/*.cpp Casillero/casilleros/*.cpp empresa/*.cpp programa/*.cpp material/*.cpp utils/*.cpp printer/*.cpp jugador/*.cpp jugador/jugadores/*.cpp meta/*.cpp meta/objetivos/*.cpp meta/objetivos/tipos/*.cpp parser/*.cpp grafo/*.cpp juego/*.cpp
	$(CXX) *.cpp edificio/*.cpp edificio/edificios/*.cpp Casillero/*.cpp Casillero/casilleros/*.cpp empresa/*.cpp programa/*.cpp material/*.cpp utils/*.cpp printer/*.cpp jugador/*.cpp jugador/jugadores/*.cpp meta/*.cpp meta/objetivos/*.cpp meta/objetivos/tipos/*.cpp  parser/*.cpp grafo/*.cpp juego/*.cpp $(CXXFLAGS) -o $(NOMBRE)

# Para compilar mas facil los test unitarios.
test_material:  test/test_material/*.cpp material/*.cpp 
	$(CXX)  test/test_material/*.cpp material/*.cpp  $(CXXFLAGS) -o test

test_edificios: test/test_edificio/*.cpp edificio/*.cpp edificio/edificios/*.cpp material/*.cpp 
	$(CXX) test/test_edificio/*.cpp edificio/*.cpp edificio/edificios/*.cpp material/*.cpp  $(CXXFLAGS) -o test

test_coordenada: test/test_coordenada/*.cpp utils/coordenada.cpp 
	$(CXX) test/test_coordenada/*.cpp utils/coordenada.cpp  $(CXXFLAGS) -o test

test_casillero: test/test_casilleros/*.cpp edificio/edificios/*.cpp material/*.cpp Casillero/*.cpp Casillero/casilleros/*.cpp utils/*.cpp edificio/*.cpp empresa/Almacen.cpp printer/table_printer.cpp empresa/mapa.cpp
	$(CXX) test/test_casilleros/*.cpp edificio/edificios/*.cpp material/*.cpp Casillero/*.cpp Casillero/casilleros/*.cpp utils/*.cpp edificio/*.cpp empresa/Almacen.cpp printer/table_printer.cpp  empresa/mapa.cpp $(CXXFLAGS) -o test

test_jugador: test/test_jugador/*.cpp edificio/edificios/*.cpp material/*.cpp Casillero/*.cpp Casillero/casilleros/*.cpp utils/*.cpp edificio/*.cpp empresa/Almacen.cpp
	$(CXX) test/test_jugador/*.cpp edificio/edificios/*.cpp material/*.cpp Casillero/*.cpp Casillero/casilleros/*.cpp utils/*.cpp edificio/*.cpp empresa/Almacen.cpp $(CXXFLAGS) -o test

#test_objetivos: test/test_objetivo/*.cpp material/*.cpp  edificio/*.cpp  edificio/edificios/*.cpp  utils/*.cpp empresa/Almacen.cpp
#	$(CXX) test/test_objetivo/*.cpp  material/*.cpp Casillero/*.cpp  edificio/*.cpp edificio/edificios/*.cpp utils/*.cpp empresa/Almacen.cpp $(CXXFLAGS) -o test

clean:
	$(RM) -v *.o
