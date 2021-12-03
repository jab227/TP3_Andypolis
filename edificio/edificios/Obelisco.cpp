#include "Obelisco.h"
#include <iostream>

const string NOMBRE = "obelisco";

Obelisco::Obelisco(std::size_t propietario) : No_Productor(NOMBRE, 0, 0, 0, 0, propietario){
}

Obelisco::Obelisco(std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos, std::size_t propietario):
	No_Productor(NOMBRE, piedra, madera, metal, maximo_permitidos, propietario){
}

void Obelisco::saludar(){
	cout << "Soy el obelisco y estoy en el casillero consultado, estoy luciendome a lo alto!" << endl;
}
