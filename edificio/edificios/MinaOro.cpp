#include "MinaOro.h"
#include <iostream>

const string NOMBRE_MATERIAL_PRODUCIDO = "andycoins", NOMBRE = "mina oro";
const int CANTIDAD_MATERIAL_PRODUCIDO = 50;

MinaOro::MinaOro() : Productor(NOMBRE, 0, 0, 0, 0, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

MinaOro::MinaOro(int piedra, int madera, int metal, int maximo_permitidos):
		Productor(NOMBRE, piedra, madera, metal, maximo_permitidos, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

void MinaOro::saludar(){
	cout << "Soy la mina de oro y estoy en el casillero consultado, estoy buscando andycoins!" << endl;
}

