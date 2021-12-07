#include "JugadorUno.h"

Jugador_Uno::Jugador_Uno(const Coordenada& coordenada)
    : Jugador(1,coordenada){}

Jugador_Uno::~Jugador_Uno() {
	// Liberar almacen
	// Liberar lista de coordenadas
}

bool Jugador_Uno::mover(const Coordenada& coordenada, const Mapa& mapa){
	std::cout << "implementar moverse" << std::endl;
	return true;
}
