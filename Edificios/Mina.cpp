#include "Mina.h"
#include <iostream>

const string NOMBRE_MATERIAL_PRODUCIDO = "piedra", NOMBRE = "mina";
const int CANTIDAD_MATERIAL_PRODUCIDO = 15;

Mina::Mina() : Productor(NOMBRE, 0, 0, 0, 0, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

Mina::Mina(int piedra, int madera, int metal, int maximo_permitidos):
		Productor(NOMBRE, piedra, madera, metal, maximo_permitidos, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

void Mina::saludar(){
	cout << "Soy la mina y estoy en el casillero consultado, estoy buscando minerales precioso!" << endl;
}

