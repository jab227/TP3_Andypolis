#include "Aserradero.h"
#include <iostream>

const string NOMBRE_MATERIAL_PRODUCIDO = "madera", NOMBRE = "aserradero";
const std::size_t CANTIDAD_MATERIAL_PRODUCIDO = 25;

Aserradero::Aserradero() : Productor(NOMBRE, 0, 0, 0, 0, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO){
}

Aserradero::Aserradero(std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos):
		Productor(NOMBRE,  piedra, madera, metal, maximo_permitidos, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO){
}

void Aserradero::saludar(){
	cout << "Soy el aserradero y estoy en el casillero consultado, estoy tranajando duro!" << endl;
}
