#include "PlantaElectrica.h"
#include <iostream>


//Energia no es un material...
const string NOMBRE = "planta electrica";
const string NOMBRE_MATERIAL_PRODUCIDO = "energia";
const int CANTIDAD_MATERIAL_PRODUCIDO = 15;

Planta_Electrica::Planta_Electrica() : Productor(NOMBRE, 0, 0, 0, 0, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

Planta_Electrica::Planta_Electrica(int piedra, int madera, int metal, int maximo_permitidos):
		Productor(NOMBRE, piedra, madera, metal, maximo_permitidos, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

void Planta_Electrica::saludar(){
	cout << "Soy la planta electrica y estoy en el casillero consultado, estoy para que la electricidad no se corte!" << endl;
}
