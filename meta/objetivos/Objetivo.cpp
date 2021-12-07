#include "Objetivo.h"

Objetivo::Objetivo(std::string titulo, Jugador* jugador) {
	this -> titulo = titulo;
	this -> cumplido = false;
	this -> jugador = jugador;
}

Objetivo::~Objetivo(){ }

bool Objetivo::esta_cumplido(){
	return this -> cumplido;
}

std::string Objetivo::obtener_titulo(){
	return this -> titulo;
}
