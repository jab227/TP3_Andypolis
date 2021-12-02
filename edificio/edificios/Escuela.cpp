#include "Escuela.h"
#include <iostream>

const string NOMBRE_MATERIAL_PRODUCIDO = "andycoins", NOMBRE = "escuela";
const int CANTIDAD_MATERIAL_PRODUCIDO = 25;

Escuela::Escuela(std::size_t propietario) : Productor(NOMBRE, 0, 0, 0, 0, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO), propietario){
}

Escuela::Escuela(int piedra, int madera, int metal, int maximo_permitidos, std::size_t propietario):
		Productor(NOMBRE,  piedra, madera, metal, maximo_permitidos, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO), propietario){
}

void Escuela::saludar(){
	cout << "Soy la escuela y estoy en el casillero consultado, estoy recolectando fondos!" << endl;
}
