#include "MinaOro.h"
#include <iostream>

const string NOMBRE_MATERIAL_PRODUCIDO = "andycoins", NOMBRE = "mina oro";
const int CANTIDAD_MATERIAL_PRODUCIDO = 50;

Mina_Oro::Mina_Oro() : Productor(NOMBRE, 0, 0, 0, 0, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

Mina_Oro::Mina_Oro(int piedra, int madera, int metal, int maximo_permitidos):
		Productor(NOMBRE, piedra, madera, metal, maximo_permitidos, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO)){
}

void Mina_Oro::saludar(){
	cout << "Soy la mina de oro y estoy en el casillero consultado, estoy recolectando monedas!" << endl;
}
