#include "Escuela.h"
#include <iostream>

const std::string NOMBRE_MATERIAL_PRODUCIDO = "andycoins", NOMBRE = "escuela";
const std::size_t CANTIDAD_MATERIAL_PRODUCIDO = 25;

Escuela::Escuela() : Productor(NOMBRE, 0, 0, 0, 0, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

Escuela::Escuela(std::size_t piedra, std::size_t madera, std::size_t metal,  std::size_t maximo_permitidos):
		Productor(NOMBRE,  piedra, madera, metal, maximo_permitidos, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

void Escuela::saludar(){
	std::cout << "Soy la "+NOMBRE+" y estoy en el casillero consultado, estoy recolectando fondos!" << std::endl;
}


Resultado_Chequeos Escuela::reparar(bool reparar_edificio){ return NO_REPARABLE;}
