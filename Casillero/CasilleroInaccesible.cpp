#include "CasilleroInaccesible.h"
#include <iostream>

Casillero_Inaccesible::Casillero_Inaccesible() {
	this -> color = AZUL;
	this -> color += NEGRO;
}

Casillero_Inaccesible::~Casillero_Inaccesible() {
}

bool Casillero_Inaccesible::esta_ocupado(){
	return true;
}

void Casillero_Inaccesible::saludar(){
	std::cout << "Soy un casillero inaccesible." << std::endl;
	std::cout << "No puedo contener nada, pero podes venir a pescar." << std::endl;
}

bool Casillero_Inaccesible::es_casillero_transitable(){
	return false;
}

bool Casillero_Inaccesible::es_casillero_construible(){
	return false;
}

std::string Casillero_Inaccesible::obtener_contenido(){
	return CONTENIDO_VACIO;
}

