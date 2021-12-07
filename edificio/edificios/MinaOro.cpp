#include "MinaOro.h"
#include <iostream>

const std::string NOMBRE_MATERIAL_PRODUCIDO = "andycoins", NOMBRE = "mina oro";
const std::size_t CANTIDAD_MATERIAL_PRODUCIDO = 50;

Mina_Oro::Mina_Oro() : Productor(NOMBRE, 0, 0, 0, 0, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

Mina_Oro::Mina_Oro(std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos):
		Productor(NOMBRE, piedra, madera, metal, maximo_permitidos, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){

}

void Mina_Oro::saludar(){
	std::cout << "Soy la mina de oro y estoy en el casillero consultado, estoy recolectando monedas!" << std::endl;
}

Resultado_Chequeos Mina_Oro::reparar(){ return NO_REPARABLE;}
