#include "Material.h"
#include <iostream>

Material::Material(){
	this -> nombre = "ninguno";
	this -> cantidad = 0;
}

Material::Material(std::string nombre, std::size_t cantidad){
	this -> nombre = nombre;
	this -> cantidad = cantidad;
}

std::string Material::obtener_nombre() const{
	return this -> nombre;
}

std::size_t Material::obtener_cantidad() const{
	return this -> cantidad;
}

void Material::cambiar_nombre(std::string nombre){
	this -> nombre = nombre;
}

void Material::cambiar_cantidad(std::size_t cantidad){
	this -> cantidad = cantidad;
}

void Material::sumar_cantidad(std::size_t cantidad){
	this -> cantidad += cantidad;
}

void Material::saludar() const{
	std::cout << "Soy el material " << this -> nombre << " y estoy en el casillero consultado." << std::endl;
}

bool Material::operator==(Material rhs) const{
	return (this -> nombre == rhs.obtener_nombre());
}

void Material::operator=(Material rhs){
	this -> nombre = rhs.obtener_nombre();
	this -> cantidad = rhs.obtener_cantidad();
}