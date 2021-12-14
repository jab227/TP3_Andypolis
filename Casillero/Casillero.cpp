#include "Casillero.h"

const std::string VACIO = "";

Casillero::Casillero() {
	this -> color = VACIO;
}

Casillero::~Casillero() {}

Casillero::Casillero(std::string color){
	this -> color = color;
}

std::string Casillero::obtener_color(){
	return this -> color;
}
