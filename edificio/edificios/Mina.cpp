#include "Mina.h"
#include <iostream>

const string NOMBRE_MATERIAL_PRODUCIDO = "piedra", NOMBRE = "mina";
const std::size_t CANTIDAD_MATERIAL_PRODUCIDO = 15;

Mina::Mina(std::size_t propietario) : Productor(NOMBRE, 0, 0, 0, 0, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO), propietario){
}

Mina::Mina(std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos, std::size_t propietario):
		Productor(NOMBRE, piedra, madera, metal, maximo_permitidos, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO), propietario){
}

void Mina::saludar(){
	cout << "Soy la mina y estoy en el casillero consultado, estoy buscando minerales precioso!" << endl;
}

