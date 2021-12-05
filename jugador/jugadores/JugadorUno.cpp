#include "JugadorUno.h"

Jugador_Uno::Jugador_Uno(Almacen *inventario) : Jugador(1, inventario){
}

Jugador_Uno::~Jugador_Uno() {
}

bool Jugador_Uno::mover(const Coordenada& coordenada, const Mapa& mapa){
	cout << "implementar moverse" << endl;
	return true;
}
