#include "Armado.h"

const std::size_t BOMBAS_A_OBTENER = 10;
const std::string NOMBRE = "Armado";

Armado::Armado(Jugador* jugador) : Objetivo(NOMBRE, jugador) {
	this -> actualizar();
}

Armado::~Armado(){ }

bool Armado::actualizar(){
	if(!this -> cumplido){
		Material bombas = this -> jugador -> obtener_inventario().obtener_material(NOMBRES_MATERIALES[BOMBAS]);
		if(bombas.obtener_cantidad() >= BOMBAS_A_OBTENER)
			this -> cumplido = true;
	}
	return this -> cumplido;
}
