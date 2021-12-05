#include "JugadorDos.h"

Jugador_Dos::Jugador_Dos(Almacen *inventario) : Jugador(2, inventario){
}

Jugador_Dos::~Jugador_Dos() {
}

bool Jugador_Dos::mover(const Coordenada& coordenada, const Mapa& mapa){
	cout << "implementar moverse" << endl;
	return true;
}
