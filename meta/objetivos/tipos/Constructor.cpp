#include "Constructor.h"

const std::string NOMBRE = "Constructor";
Constructor::Constructor(Jugador* jugador) : Objetivo(NOMBRE, jugador) {
}

Constructor::~Constructor(){ }

bool Constructor::actualizar(){
	std::cout << "Implementar actualizar constructor" << std::endl;
	return false;
}
