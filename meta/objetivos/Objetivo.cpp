#include "Objetivo.h"

Objetivo::Objetivo(std::string titulo, Jugador* jugador): titulo(titulo), jugador(jugador), cumplido(false){ }

Objetivo::~Objetivo(){ }

bool Objetivo::esta_cumplido(){
	return this -> cumplido;
}

std::string Objetivo::obtener_titulo(){
	return this -> titulo;
}
