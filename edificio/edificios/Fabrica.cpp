#include "Fabrica.h"
#include <iostream>

const std::string NOMBRE_MATERIAL_PRODUCIDO = "metal", NOMBRE = "fabrica";
const std::size_t CANTIDAD_MATERIAL_PRODUCIDO = 40;
const std::size_t MAX_VIDA = 2; //Si recibe dos ataques, se destruye.

Fabrica::Fabrica() : Productor(NOMBRE, 0, 0, 0, 0, MAX_VIDA, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

Fabrica::Fabrica(std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos):
		Productor(NOMBRE, piedra, madera, metal, maximo_permitidos, MAX_VIDA ,Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

void Fabrica::saludar(){
	std::cout << "Soy la "+NOMBRE+" y estoy en el casillero consultado, estoy funcionando para vos!" << std::endl;
}

Resultado_Chequeos Fabrica::reparar(bool reparar_edificio){
	Resultado_Chequeos resultado = NO_REPARABLE;
	if(this -> obtener_vida() < MAX_VIDA){
		resultado = EXITO;
		if(reparar_edificio)
			this -> recuperar_vida();

	}
	return resultado;
}


