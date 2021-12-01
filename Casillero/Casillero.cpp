#include "Casillero.h"

Casillero::Casillero() {
	this -> color = "";
}

Casillero::~Casillero() {

}

std::string Casillero::obtener_color(){
	return this -> color;
}
