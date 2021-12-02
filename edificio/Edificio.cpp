#include "Edificio.h"
#include <iostream>

Edificio::Edificio() {
	this->nombre = EDIFICIO_VACIO;
	this->materiales[0] = 0;
	this->materiales[1] = 0;
	this->materiales[2] = 0;
	this->maximo_permitidos = 0;
	this->construidos = 0;
	this->propietario = 0;
}

Edificio::Edificio(string nombre, std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos, std::size_t propietario){
	this->nombre = nombre;
	this->materiales[PIEDRA] = piedra;
	this->materiales[MADERA] = madera;
	this->materiales[METAL] = metal;
	this->maximo_permitidos = maximo_permitidos;
	this->construidos = 0;
	this->propietario = propietario;
}

Edificio::~Edificio(){

}

string Edificio::obtener_nombre() const {
	return this->nombre;
}

std::size_t Edificio::obtener_cant_material(string material){
	std::size_t cantidad = 0, i = 0;
	bool fin = false;
	while(i < CANT_MATERIALES_EDIFICIOS && !fin){
		if(MATERTIALES_EDIFICIOS[i] == material){
			cantidad = this->materiales[i];
			fin = true;
		}
		i++;
	}
	return cantidad;
}

std::size_t Edificio::obtener_max_permitidos(){
	return this->maximo_permitidos;
}

/*void Edificio::saludar(){
	cout << "Soy un/a " << this->nombre << " y estoy en el casillero consultado." << endl;
} */

bool Edificio::vacio(){
	return this->nombre == EDIFICIO_VACIO;
}

void Edificio::modificar_construidos(std::size_t n){
	if(n < this->maximo_permitidos)
		this->construidos = n;
}

void Edificio::aumentar_construidos(){
	this->modificar_construidos(construidos + 1);

}

void Edificio::disminuir_construidos(){
	this->modificar_construidos(construidos - 1);	
}


std::size_t Edificio::obtener_construidos(){
	return this->construidos;
}

std::size_t Edificio::obtener_propietario(){
	return this->propietario;
}

/* Por ahora, inutiles
bool Edificio::operator==(const Edificio &rhs){
	return this->nombre == rhs.obtener_nombre();
}

bool Edificio::operator!=(const Edificio &rhs){
	return this->nombre != rhs.obtener_nombre();
}
*/
