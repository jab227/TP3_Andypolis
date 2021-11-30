#include "Fabrica.h"
#include <iostream>

const string NOMBRE_MATERIAL_PRODUCIDO = "metal", NOMBRE = "fabrica";
const int CANTIDAD_MATERIAL_PRODUCIDO = 40;

Fabrica::Fabrica() : Productor(NOMBRE, 0, 0, 0, 0, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

Fabrica::Fabrica(int piedra, int madera, int metal, int maximo_permitidos):
		Productor(NOMBRE, piedra, madera, metal, maximo_permitidos, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

void Fabrica::saludar(){
	cout << "Soy la fabrica y estoy en el casillero consultado, estoy funcionando para vos!" << endl;
}
