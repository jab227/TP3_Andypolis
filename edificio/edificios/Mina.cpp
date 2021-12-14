#include "Mina.h"
#include <iostream>

const std::string NOMBRE_MATERIAL_PRODUCIDO = "piedra", NOMBRE = "mina";
const std::size_t CANTIDAD_MATERIAL_PRODUCIDO = 15;
const std::size_t MAX_VIDA = 2; //Si recibe dos ataques, se destruye.

Mina::Mina() : Productor(NOMBRE, 0, 0, 0, 0, MAX_VIDA ,Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

Mina::Mina(std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos):
		Productor(NOMBRE, piedra, madera, metal, maximo_permitidos, MAX_VIDA ,Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

void Mina::saludar(){
	std::cout << "Soy la "+NOMBRE+" y estoy en el casillero consultado, estoy buscando minerales precioso!" << std::endl;
}

Resultado_Chequeos Mina::reparar(bool reparar_edificio){
	Resultado_Chequeos resultado = NO_REPARABLE;
	if(this -> obtener_vida() < MAX_VIDA){
		resultado = EXITO;
		if(reparar_edificio)
			this -> recuperar_vida();
	}
	return resultado;
}
