#include "Letrado.h"

const std::string NOMBRE = "Letrado";

Letrado::Letrado(Jugador* jugador) : Objetivo(NOMBRE,jugador) {
}

Letrado::~Letrado(){ }

bool Letrado::actualizar(){
	std::cout << "Implementar actualizar letrado" << std::endl;
	return false;
}

