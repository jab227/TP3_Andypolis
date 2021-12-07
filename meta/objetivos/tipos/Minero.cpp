#include "Minero.h"

Minero::Minero(Jugador* jugador) : Objetivo(jugador) {
	this -> titulo = "Minero";
}

Minero::~Minero(){ }

bool Minero::actualizar(){
	std::cout << "Implementar actualizar minero" << std::endl;
	return false;
}
