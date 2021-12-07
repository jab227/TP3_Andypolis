#include "CasilleroInaccesible.h"
#include <iostream>

Casillero_Inaccesible::Casillero_Inaccesible(): Casillero(AZUL + NEGRO)  {
}

Casillero_Inaccesible::~Casillero_Inaccesible() {
}

bool Casillero_Inaccesible::esta_ocupado() const {
	return true;
}

void Casillero_Inaccesible::saludar() const{
	std::cout << "Soy un casillero inaccesible." << std::endl;
	std::cout << "No puedo contener nada, pero podes venir a pescar." << std::endl;
}


std::string Casillero_Inaccesible::obtener_contenido() const{ return CONTENIDO_VACIO;}

Resultado_Chequeos Casillero_Inaccesible::construir_edificio(Edificio* edificio){
	return CASILLERO_NO_CONSTRUIBLE;
}

Edificio* Casillero_Inaccesible::agregar_lista_edificio( Coordenada* coordenada, Lista<Edificio>* &lista_construidos){
	Edificio* edificio = nullptr;
	return edificio;
}

//Provisorio
bool Casillero_Inaccesible::es_casillero_transitable(){
	return false;
}

Resultado_Chequeos Casillero_Inaccesible::demoler_edificio(){
	return CASILLERO_NO_CONSTRUIBLE;
}

void Casillero_Inaccesible::recoger_material(Almacen* inventario){}

Resultado_Chequeos Casillero_Inaccesible::reparar_edificio() {return CASILLERO_NO_CONSTRUIBLE;}

Resultado_Chequeos Casillero_Inaccesible::atacar_edificio() {
	return NO_EXISTE;
}