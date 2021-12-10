#include "Betun.h"

Betun::Betun(): Casillero_Transitable(GRIS_OSCURO + BLANCO) {
}

void Betun::saludar() const{
	std::cout << "Soy un casillero transitable del tipo Betun." << std::endl;
	if(this -> esta_ocupado())
		saludo_material();
	else
		std::cout << "No tengo ningun material en mi." << std::endl;
}

char Betun::obtener_identificador(){
	return BETUN;
}

