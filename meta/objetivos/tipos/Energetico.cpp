#include "Energetico.h"

const std::size_t ENERGIA_A_OBTENER = 100;
const std::string NOMBRE = "Energetico";

Energetico::Energetico(Jugador* jugador) : Objetivo(NOMBRE, jugador) {
}

bool Energetico::actualizar(){
	if(!this -> cumplido)
		if(this -> jugador -> obtener_energia() >= ENERGIA_A_OBTENER)
			this -> cumplido = true;

	return this -> cumplido;
}
