#include "PlantaElectrica.h"
#include <iostream>

const string NOMBRE = "planta electrica";

Planta_Electrica::Planta_Electrica() : No_Productor(NOMBRE, 0, 0, 0, 0){
}

Planta_Electrica::Planta_Electrica(int piedra, int madera, int metal, int maximo_permitidos):
	No_Productor(NOMBRE, piedra, madera, metal, maximo_permitidos){

}

void Planta_Electrica::saludar(){
	cout << "Soy la planta electrica y estoy en el casillero consultado, estoy para que la electricidad no se corte!" << endl;
}
