#include "JugadorDos.h"

<<<<<<< HEAD
Jugador_Dos::Jugador_Dos(Almacen *inventario) : Jugador(2, inventario){}

Jugador_Dos::Jugador_Dos(Almacen *inventario, Lista<Coordenada*>* edificios)
    : Jugador(2, inventario, edificios){}
=======
Jugador_Dos::Jugador_Dos(const Coordenada& coordenada)
    : Jugador(2, coordenada){}
>>>>>>> DiccionarioEdificios

Jugador_Dos::~Jugador_Dos() {
	// Liberar almacen
	// Liberar lista de coordenadas
}

bool Jugador_Dos::mover(const Coordenada& coordenada, const Mapa& mapa){
	cout << "implementar moverse" << endl;
	return true;
}
