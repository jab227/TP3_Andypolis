#include "Minero.h"

Minero::Minero(Jugador* jugador) : Objetivo(jugador) {
	this -> titulo = "Minero";
}

bool Minero::actualizar(){
	std::cout << "Implementar actualizar letrado" << std::endl;
	return false;
}
