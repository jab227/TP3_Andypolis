#include "CasilleroConstruible.h"
#include <iostream>

Casillero_Construible::Casillero_Construible() {
	this -> ocupado = false;
	this -> edificio = nullptr;
	this -> color = VERDE;
	this -> color += NEGRO;
}

Casillero_Construible::~Casillero_Construible() {
	if(this -> ocupado)
		delete this -> edificio;
}

void Casillero_Construible::construir_edificio(Edificio* edificio){
	this -> edificio = edificio;
	this -> ocupado = true;
}

Edificio* Casillero_Construible::demoler_edificio(){
	Edificio* edificio = nullptr;
	if(this -> ocupado){
		edificio = this -> edificio;
		this -> edificio = nullptr;
		this -> ocupado = false;
	}
	return edificio;
}

bool Casillero_Construible::esta_ocupado(){
	return this -> ocupado;
}

void Casillero_Construible::saludar(){
	cout << "Soy un casillero construible." << endl;
	if(this -> ocupado)
		this -> edificio -> saludar();
	else
		cout << "No tengo ningun edificio construido." << endl;
}

bool Casillero_Construible::es_casillero_transitable(){
	return false;
}

bool Casillero_Construible::es_casillero_construible(){
	return true;
}

string Casillero_Construible::obtener_contenido(){
	string nombre = EDIFICIO_VACIO;
	if(this -> ocupado)
		nombre = this -> edificio -> obtener_nombre();
	return nombre;
}




