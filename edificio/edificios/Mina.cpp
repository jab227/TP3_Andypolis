#include "Mina.h"
#include <iostream>

const string NOMBRE_MATERIAL_PRODUCIDO = "piedra", NOMBRE = "mina";
const std::size_t CANTIDAD_MATERIAL_PRODUCIDO = 15;
const std::size_t MAX_VIDA = 2; //Si recibe dos ataques, se destruye.

Mina::Mina() : Productor(NOMBRE, 0, 0, 0, 0, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

Mina::Mina(std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos):
		Productor(NOMBRE, piedra, madera, metal, maximo_permitidos, MAX_VIDA ,Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

void Mina::saludar(){
	cout << "Soy la "+NOMBRE+" y estoy en el casillero consultado, estoy buscando minerales precioso!" << endl;
}


Resultado_Chequeos Mina::reparar(){ 
	Resultado_Chequeos resultado = NO_REPARABLE;
	if(this -> obtener_vida() < MAX_VIDA){
		this -> recuperar_vida();
		resultado = EXITO;
	}
	return resultado;
}