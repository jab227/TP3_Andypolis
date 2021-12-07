#include "Cansado.h"

const std::size_t ENERGIA_DESEADA = 0;

Cansado::Cansado(Jugador* jugador) : Objetivo(jugador) {
	this -> titulo = "Cansado";
}

bool Cansado::actualizar(){
	if(!this -> cumplido)
		if(this -> jugador -> obtener_energia() <= ENERGIA_DESEADA)
			this -> cumplido = true;

	return this -> cumplido;
}

