#include "Escuela.h"
#include <iostream>

const string NOMBRE_MATERIAL_PRODUCIDO = "andycoins", NOMBRE = "escuela";
const int CANTIDAD_MATERIAL_PRODUCIDO = 25;

Escuela::Escuela() : Productor(NOMBRE, 0, 0, 0, 0, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

Escuela::Escuela(int piedra, int madera, int metal, int maximo_permitidos):
		Productor(NOMBRE,  piedra, madera, metal, maximo_permitidos, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){

void Escuela::saludar(){
	cout << "Soy la escuela y estoy en el casillero consultado, estoy formando chicos!" << endl;
}
