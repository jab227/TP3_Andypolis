#include "Minero.h"

const std::string NOMBRE = "Minero";
Minero::Minero(Jugador* jugador) : Objetivo(NOMBRE,jugador) {
}

Minero::~Minero(){ }

bool Minero::actualizar(){
	std::cout << "Implementar actualizar minero" << std::endl;
	return false;
}
