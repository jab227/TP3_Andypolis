#include "CasilleroInaccesible.h"
#include <iostream>

Casillero_Inaccesible::Casillero_Inaccesible(): Casillero(AZUL + NEGRO)  {
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


std::string Casillero_Inaccesible::obtener_contenido(){
	return CONTENIDO_VACIO;
}

bool Casillero_Inaccesible::construir_edificio(Edificio* edificio){
	cout <<  "La ubicacion ingresada no es construible." << endl;
	return false;
}

Edificio* agregar_lista_edificio( std::size_t* coordenadas, Lista<string> &lista_nombres, Lista<Lista<std::size_t*>*> &lista_coordenadas){
	delete[] coordenadas;
	Edificio* edificio = nullptr;
	return edificio;
}

//Provisorio
bool es_casillero_transitable(){return false;}

//Agregar demoler_edificio en inacc y transitables.
Edificio* Casillero_Inaccesible::demoler_edificio(){
	Edificio* edificio = nullptr;
	return edificio;
}