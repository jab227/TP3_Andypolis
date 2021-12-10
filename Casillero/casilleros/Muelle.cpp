#include "Muelle.h"

Muelle::Muelle(): Casillero_Transitable(MARRON + BLANCO) {
}

void Muelle::saludar() const{
	std::cout << "Soy un casillero transitable del tipo Muelle." << std::endl;
	if(this -> esta_ocupado())
		saludo_material();
	else
		std::cout << "No tengo ningun material en mi." << std::endl;
}

char Muelle::obtener_identificador(){
	return MUELLE;
}
