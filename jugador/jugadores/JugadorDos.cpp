#include "JugadorDos.h"

Jugador_Dos::Jugador_Dos(Almacen *inventario) : Jugador(2, inventario){}

Jugador_Dos::Jugador_Dos(Almacen *inventario, Lista<Coordenada*>* edificios)
    : Jugador(2, inventario, edificios){}

Jugador_Uno::~Jugador_Uno() {
	// Liberar almacen
	// Liberar lista de coordenadas
}

bool Jugador_Dos::mover(const Coordenada& coordenada, const Mapa& mapa){
	cout << "implementar moverse" << endl;
	return true;
}
