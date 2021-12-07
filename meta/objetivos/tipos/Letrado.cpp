#include "Letrado.h"

const std::string NOMBRE = "Letrado.h";

Letrado::Letrado(Jugador* jugador) : Objetivo(NOMBRE,jugador) {
}

Letrado::~Letrado(){ }

bool Letrado::actualizar(){
	std::cout << "Implementar actualizar letrado" << std::endl;
	return false;
}

