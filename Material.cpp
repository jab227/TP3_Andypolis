#include "Material.h"
#include <iostream>

Material::Material(){
	this -> nombre = "ninguno";
	this -> cantidad = 0;
}

Material::Material(string nombre, int cantidad){
	this -> nombre = nombre;
	this -> cantidad = cantidad;
}

string Material::obtener_nombre(){
	return this -> nombre;
}

int Material::obtener_cantidad(){
	return this -> cantidad;
}

void Material::cambiar_nombre(string nombre){
	this -> nombre = nombre;
}
void Material::cambiar_cantidad(int cantidad){
	this -> cantidad = cantidad;
}

void Material::saludar(){
	cout << "Soy el material " << this -> nombre << " y estoy en el casillero consultado." << endl;
}
