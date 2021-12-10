#include "Camino.h"

Camino::Camino(): Casillero_Transitable(GRIS + NEGRO) {
}

void Camino::saludar() const{
	std::cout << "Soy un casillero transitable del tipo Camino." << std::endl;
	if(this -> esta_ocupado())
		saludo_material();
	else
		std::cout << "No tengo ningun material en mi." << std::endl;
}

char obtener_identificador(){
	return CAMINO;
}
