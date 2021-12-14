#include "Obelisco.h"
#include <iostream>

const std::string NOMBRE = "obelisco";

Obelisco::Obelisco() : No_Productor(NOMBRE, 0, 0, 0, 0){
}

Obelisco::Obelisco(std::size_t piedra, std::size_t madera, std::size_t metal, std::size_t maximo_permitidos):
	No_Productor(NOMBRE, piedra, madera, metal, maximo_permitidos){
}

void Obelisco::saludar(){
	std::cout << "Soy el "+NOMBRE+" y estoy en el casillero consultado, estoy luciendome a lo alto!" << std::endl;
}

Resultado_Chequeos Obelisco::reparar(bool reparr_edificio){ return NO_REPARABLE;}

