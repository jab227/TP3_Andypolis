#include "JugadorDos.h"

Jugador_Dos::Jugador_Dos(const Coordenada& coordenada)
    : Jugador(2, coordenada){}

Jugador_Dos::~Jugador_Dos() {
	// Liberar almacen
	// Liberar lista de coordenadas
}

bool Jugador_Dos::mover(const Coordenada& coordenada, const Mapa& mapa){
	std::cout << "implementar moverse" << std::endl;
	return true;
}
