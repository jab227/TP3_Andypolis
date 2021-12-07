#include "Constructor.h"

Constructor::Constructor(Jugador* jugador) : Objetivo(jugador) {
	this -> titulo = "Constructor";
}

bool Constructor::actualizar(){
	std::cout << "Implementar actualizar letrado" << std::endl;
	return false;
}
