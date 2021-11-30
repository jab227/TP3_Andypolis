#include "Escuela.h"
#include <iostream>

const string NOMBRE = "escuela";

Escuela::Escuela() : No_Productor(NOMBRE, 0, 0, 0, 0){
}

Escuela::Escuela(int piedra, int madera, int metal, int maximo_permitidos):
	No_Productor(NOMBRE, piedra, madera, metal, maximo_permitidos){

}

void Escuela::saludar(){
	cout << "Soy la escuela y estoy en el casillero consultado, estoy formando chicos!" << endl;
}
