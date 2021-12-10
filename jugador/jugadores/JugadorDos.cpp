#include "JugadorDos.h"

Jugador_Dos::Jugador_Dos(const Coordenada& coordenada)
    : Jugador(2, coordenada){}

Jugador_Dos::~Jugador_Dos() {
	// Liberar almacen
	// Liberar lista de coordenadas
}

std::size_t Jugador_Dos::obtener_costo_terreno(Coordenada coordenada, Mapa* mapa){
	std::cout << "Implementar costos" << std::endl;
	return 5;
}
