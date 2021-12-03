#include "CasilleroTransitable.h"
#include <iostream>

Casillero_Transitable::Casillero_Transitable(): Casillero(GRIS + NEGRO) {
	this -> material = nullptr;
}

Casillero_Transitable::~Casillero_Transitable() {
	if(this -> esta_ocupado())
		delete this -> material;
}

void Casillero_Transitable::agregar_material(Material* material){
	this -> material = material;
	this -> ocupado = true;
}

Material* Casillero_Transitable::eliminar_material(){
	Material* material = nullptr;
	if(this -> esta_ocupado()){
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
	if(this -> esta_ocupado())
		this -> material -> saludar();
	else
		cout << "No tengo ningun material en mi." << endl;
}

string Casillero_Transitable::obtener_contenido(){
	string nombre = CONTENIDO_VACIO;
	if(this -> esta_ocupado())
		nombre = this -> material -> obtener_nombre();
	return nombre;
}

Edificio* agregar_lista_edificio( int* coordenadas, Lista<string> &lista_nombres, Lista<Lista<int*>*> &lista_coordenadas){
	delete[] coordenadas;
	Edificio* edificio = nullptr;
	return edificio;
}

bool Casillero_Transitable::construir_edificio(Edificio* edificio){
	cout <<  "La ubicacion ingresada no es construible." << endl;
	return false;
}
	
//Provisorio
bool es_casillero_transitable(){
	return true;
}

//Agregar demoler_edificio en inacc y transitables.
Edificio* Casillero_Transitable::demoler_edificio(){
	Edificio* edificio = nullptr;
	return edificio;
}