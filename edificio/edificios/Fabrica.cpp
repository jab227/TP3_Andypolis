#include "Fabrica.h"
#include <iostream>

const string NOMBRE_MATERIAL_PRODUCIDO = "metal", NOMBRE = "fabrica";
const int CANTIDAD_MATERIAL_PRODUCIDO = 40;

Fabrica::Fabrica(std::size_t propietario) : Productor(NOMBRE, 0, 0, 0, 0, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO), propietario){
}

Fabrica::Fabrica(int piedra, int madera, int metal, int maximo_permitidos, std::size_t propietario):
		Productor(NOMBRE, piedra, madera, metal, maximo_permitidos, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO), propietario){
}

void Fabrica::saludar(){
	cout << "Soy la fabrica y estoy en el casillero consultado, estoy funcionando para vos!" << endl;
}
