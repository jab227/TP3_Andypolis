#include "Objetivo.h"

Objetivo::Objetivo(std::string titulo, Jugador* jugador) {
	this -> titulo = titulo;
	this -> cumplido = false;
	this -> jugador = jugador;
}

bool Objetivo::esta_cumplido(){
	return this -> cumplido;
}
