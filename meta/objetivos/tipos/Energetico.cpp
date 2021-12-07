#include "Energetico.h"

const std::size_t ENERGIA_A_OBTENER = 100;

Energetico::Energetico(Jugador* jugador) : Objetivo(jugador) {
	this -> titulo = "Energetico";
}

Energetico::~Energetico(){ }

bool Energetico::actualizar(){
	if(!this -> cumplido)
		if(this -> jugador -> obtener_energia() >= ENERGIA_A_OBTENER)
			this -> cumplido = true;

	return this -> cumplido;
}
