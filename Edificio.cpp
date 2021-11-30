#include "Edificio.h"
#include <iostream>

Edificio::Edificio() {
	this -> nombre = EDIFICIO_VACIO;
	this -> materiales[0] = 0;
	this -> materiales[1] = 0;
	this -> materiales[2] = 0;
	this -> maximo_permitidos = 0;
	this -> construidos = 0;
}

Edificio::Edificio(string nombre, int piedra, int madera, int metal, int maximo_permitidos){
	this -> nombre = nombre;
	this -> materiales[PIEDRA] = piedra;
	this -> materiales[MADERA] = madera;
	this -> materiales[METAL] = metal;
	this -> maximo_permitidos = maximo_permitidos;
	this -> construidos = 0;
}

Edificio::~Edificio(){

}

string Edificio::obtener_nombre(){
	return this -> nombre;
}

int Edificio::obtener_cant_material(string material){
	int cantidad = 0, i = 0;
	bool fin = false;
	while(i < CANT_MATERIALES_EDIFICIOS && !fin){
		if(MATERTIALES_EDIFICIOS[i] == material){
			cantidad = this -> materiales[i];
			fin = true;
		}
		i++;
	}
	return cantidad;
}

int Edificio::obtener_max_permitidos(){
	return this -> maximo_permitidos;
}

/*void Edificio::saludar(){
	cout << "Soy un/a " << this -> nombre << " y estoy en el casillero consultado." << endl;
} */

bool Edificio::vacio(){
	return this -> nombre == EDIFICIO_VACIO;
}

void Edificio::modificar_construidos(int n){
	this -> construidos = n;
}

int Edificio::obtener_construidos(){
	return this -> construidos;
}

