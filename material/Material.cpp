#include "Material.h"
#include <iostream>

Material::Material(){
	this -> nombre = "ninguno";
	this -> cantidad = 0;
}

Material::Material(string nombre, std::size_t cantidad){
	this -> nombre = nombre;
	this -> cantidad = cantidad;
}

string Material::obtener_nombre(){
	return this -> nombre;
}

std::size_t Material::obtener_cantidad(){
	return this -> cantidad;
}

void Material::cambiar_nombre(string nombre){
	this -> nombre = nombre;
}
void Material::cambiar_cantidad(std::size_t cantidad){
	this -> cantidad = cantidad;
}

void Material::sumar_cantidad(std::size_t cantidad){
	this -> cantidad += cantidad;
}

void Material::saludar(){
	cout << "Soy el material " << this -> nombre << " y estoy en el casillero consultado." << endl;
}

bool Material::operator==(Material rhs){
	return (this -> nombre == rhs.obtener_nombre());
}

void Material::operator=(Material rhs){
	this -> nombre = rhs.obtener_nombre();
}