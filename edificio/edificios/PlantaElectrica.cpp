#include "PlantaElectrica.h"
#include <iostream>


//Energia no es un material...
const std::string NOMBRE = "planta electrica";
const std::string NOMBRE_MATERIAL_PRODUCIDO = "energia";
const std::size_t CANTIDAD_MATERIAL_PRODUCIDO = 15;

Planta_Electrica::Planta_Electrica() : Productor(NOMBRE, 0, 0, 0, 0, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

 
Planta_Electrica::Planta_Electrica(std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos):
		Productor(NOMBRE, piedra, madera, metal, maximo_permitidos, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
 
}

void Planta_Electrica::saludar(){
	std::cout << "Soy la "+NOMBRE+" y estoy en el casillero consultado, estoy para que la electricidad no se corte!" << std::endl;
}

Resultado_Chequeos Planta_Electrica::reparar(bool reparar_edificio){ return NO_REPARABLE;}
