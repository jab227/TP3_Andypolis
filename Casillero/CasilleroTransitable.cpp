#include "CasilleroTransitable.h"
#include <iostream>

Casillero_Transitable::Casillero_Transitable() {
	this -> ocupado = false;
	this -> material = nullptr;
	this -> color = GRIS;
	this -> color += NEGRO;
}

Casillero_Transitable::~Casillero_Transitable() {
	if(this -> ocupado)
		delete this -> material;
}

void Casillero_Transitable::agregar_material(Material* material){
	this -> material = material;
	this -> ocupado = true;
}

Material* Casillero_Transitable::eliminar_material(){
	Material* material = nullptr;
	if(this -> ocupado){
		material = this -> material;
		this -> material = nullptr;
		this -> ocupado = false;
	}
	return material;
}

bool Casillero_Transitable::esta_ocupado(){
	return this -> ocupado;
}

void Casillero_Transitable::saludar(){
	cout << "Soy un casillero transitable." << endl;
	if(this -> ocupado)
		this -> material -> saludar();
	else
		cout << "No tengo ningun material en mi." << endl;
}

bool Casillero_Transitable::es_casillero_transitable(){
	return true;
}

bool Casillero_Transitable::es_casillero_construible(){
	return false;
}

string Casillero_Transitable::obtener_contenido(){
	string nombre = CONTENIDO_VACIO;
	if(this -> ocupado)
		nombre = this -> material -> obtener_nombre();
	return nombre;
}

