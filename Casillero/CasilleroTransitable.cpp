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
}

Material* Casillero_Transitable::eliminar_material(){
	Material* material = nullptr;
	if(this -> esta_ocupado()){
		material = this -> material;
		this -> material = nullptr;
	}
	return material;
}

bool Casillero_Transitable::esta_ocupado(){
	return !(this -> material == nullptr);
}

void Casillero_Transitable::saludar(){
	cout << "Soy un casillero transitable." << endl;
	if(this -> esta_ocupado())
		this -> material -> saludar();
	else
		cout << "No tengo ningun material en mi." << endl;
}

std::string Casillero_Transitable::obtener_contenido(){
	string nombre = CONTENIDO_VACIO;
	if(this -> esta_ocupado())
		nombre = this -> material -> obtener_nombre();
	return nombre;
}

Edificio* Casillero_Transitable::agregar_lista_edificio(std::size_t fila, std::size_t columna, Lista<string> &lista_nombres, Lista<Lista<std::size_t*>*> &lista_coordenadas){
	Edificio* edificio = nullptr;
	return edificio;
}

bool Casillero_Transitable::construir_edificio(Edificio* edificio){
	cout <<  "La ubicacion ingresada no es construible." << endl;
	return false;
}
	
//Provisorio
bool Casillero_Transitable::es_casillero_transitable(){
	return true;
}

//Agregar demoler_edificio en inacc y transitables.
std::string Casillero_Transitable::demoler_edificio(){
	return "";
}