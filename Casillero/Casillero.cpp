#include "Casillero.h"

Casillero::Casillero() {
	this -> color = "";
}

Casillero::~Casillero() {

}

Casillero::Casillero(std::string color){
	this -> color = color;
}

std::string Casillero::obtener_color(){
	return this -> color;
}
