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


void Casillero_Inaccesible::obtener_contenido(Edificio*& edificio) const{ edificio = nullptr;}
void Casillero_Inaccesible::obtener_contenido(Material*& material) const{ material = nullptr;}

Resultado_Chequeos Casillero_Inaccesible::construir_edificio(Edificio* edificio){
	return CASILLERO_NO_CONSTRUIBLE;
}

Edificio* Casillero_Inaccesible::agregar_lista_edificio( Coordenada* coordenada, Lista<Edificio>* &lista_construidos){
//	Edificio* edificio = nullptr;
//	return edificio;
}

//Provisorio
bool Casillero_Inaccesible::es_casillero_transitable(){
	return false;
}

//Agregar demoler_edificio en inacc y transitables.
std::string Casillero_Inaccesible::demoler_edificio(){
	return "";
}

void Casillero_Inaccesible::recoger_material(Almacen* inventario){}
