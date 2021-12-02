#include "MinaOro.h"
#include <iostream>

const string NOMBRE_MATERIAL_PRODUCIDO = "andycoins", NOMBRE = "mina oro";
const int CANTIDAD_MATERIAL_PRODUCIDO = 50;

Mina_Oro::Mina_Oro(std::size_t propietario) : Productor(NOMBRE, 0, 0, 0, 0, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO), propietario){
}

Mina_Oro::Mina_Oro(int piedra, int madera, int metal, int maximo_permitidos, std::size_t propietario):
		Productor(NOMBRE, piedra, madera, metal, maximo_permitidos, Material(NOMBRE_MATERIAL_PRODUCIDO, CANTIDAD_MATERIAL_PRODUCIDO), propietario){
}

void Mina_Oro::saludar(){
	cout << "Soy la mina de oro y estoy en el casillero consultado, estoy recolectando monedas!" << endl;
}
