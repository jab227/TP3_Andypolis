#include "Objetivo.h"

Objetivo::Objetivo(Jugador* jugador) {
	this -> cumplido = false;
	this -> jugador = jugador;
}

bool Objetivo::esta_cumplido(){
	return this -> cumplido;
}

std::string Objetivo::obtener_titulo(){
	return this -> titulo;
}
