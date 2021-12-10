#include "JugadorUno.h"

Jugador_Uno::Jugador_Uno(const Coordenada& coordenada)
    : Jugador(1,coordenada){}

Jugador_Uno::~Jugador_Uno() {
	// Liberar almacen
	// Liberar lista de coordenadas
}

std::size_t Jugador_Uno::obtener_costo_terreno(Coordenada coordenada, Mapa* mapa){
	std::cout << "Implementar costos" << std::endl;
	return 5;
}
