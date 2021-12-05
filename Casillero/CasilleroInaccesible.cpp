#include "CasilleroInaccesible.h"
#include <iostream>

Casillero_Inaccesible::Casillero_Inaccesible(): Casillero(AZUL + NEGRO)  {
}

Casillero_Inaccesible::~Casillero_Inaccesible() {
}

bool Casillero_Inaccesible::esta_ocupado() const{
	return true;
}

void Casillero_Inaccesible::saludar() const{
	std::cout << "Soy un casillero inaccesible." << std::endl;
	std::cout << "No puedo contener nada, pero podes venir a pescar." << std::endl;
}


void Casillero_Inaccesible::obtener_contenido(Edificio*& edificio) const{ edificio = nullptr;}
void Casillero_Inaccesible::obtener_contenido(Material*& material) const{ material = nullptr;}

bool Casillero_Inaccesible::construir_edificio(Edificio* edificio){
	cout <<  "La ubicacion ingresada no es construible." << endl;
	return false;
}

Edificio* Casillero_Inaccesible::agregar_lista_edificio(std::size_t fila, std::size_t columna, Lista<string> &lista_nombres, Lista<Lista<std::size_t*>*> &lista_coordenadas){
	Edificio* edificio = nullptr;
	return edificio;
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