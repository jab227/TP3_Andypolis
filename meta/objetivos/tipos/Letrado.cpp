#include "Letrado.h"

Letrado::Letrado(Jugador* jugador) : Objetivo(jugador) {
	this -> titulo = "Letrado.h";
}

Letrado::~Letrado(){ }

bool Letrado::actualizar(){
	std::cout << "Implementar actualizar letrado" << std::endl;
	return false;
}

