#include "Fabrica.h"
#include <iostream>

const string NOMBRE_MATERIAL_PRODUCIDO = "metal", NOMBRE = "fabrica";
const std::size_t CANTIDAD_MATERIAL_PRODUCIDO = 40;

Fabrica::Fabrica() : Productor(NOMBRE, 0, 0, 0, 0, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

Fabrica::Fabrica(std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos):
		Productor(NOMBRE, piedra, madera, metal, maximo_permitidos, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

void Fabrica::saludar(){
	cout << "Soy la "+NOMBRE+" y estoy en el casillero consultado, estoy funcionando para vos!" << endl;
}



Resultado_Chequeos reparar(){ 
//TODO: Implementar
}