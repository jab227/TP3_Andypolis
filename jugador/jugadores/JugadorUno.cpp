#include "JugadorUno.h"

Jugador_Uno::Jugador_Uno(Almacen *inventario, Lista<Coordenada*>* edificios)
    : Jugador(1, inventario, edificios){}

Jugador_Uno::Jugador_Uno(Almacen *inventario) : Jugador(1, inventario){
}

Jugador_Uno::~Jugador_Uno() {
	// Liberar almacen
	// Liberar lista de coordenadas
}

bool Jugador_Uno::mover(const Coordenada& coordenada, const Mapa& mapa){
	cout << "implementar moverse" << endl;
	return true;
}
