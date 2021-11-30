#include "Obelisco.h"
#include <iostream>

const string NOMBRE = "obelisco";

Obelisco::Obelisco() : No_Productor(NOMBRE, 0, 0, 0, 0){
}

Obelisco::Obelisco(int piedra, int madera, int metal, int maximo_permitidos):
	No_Productor(NOMBRE, piedra, madera, metal, maximo_permitidos){

}

void Obelisco::saludar(){
	cout << "Soy el obelisco y estoy en el casillero consultado, estoy luciendome a lo alto!" << endl;
}
