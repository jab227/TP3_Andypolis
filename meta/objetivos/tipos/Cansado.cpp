#include "Cansado.h"

const std::size_t ENERGIA_DESEADA = 0;
const std::string NOMBRE ="Cansado";

Cansado::Cansado(Jugador* jugador) : Objetivo(NOMBRE, jugador) {
}

Cansado::~Cansado(){ }

bool Cansado::actualizar(){
	if(!this -> cumplido)
		if(this -> jugador -> obtener_energia() <= ENERGIA_DESEADA)
			this -> cumplido = true;

	return this -> cumplido;
}

