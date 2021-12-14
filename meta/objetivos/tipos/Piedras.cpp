#include "Piedras.h"

const std::size_t PIEDRAS_A_OBTENER = 50e3;
const std::string NOMBRE = "Edad de piedra";

Piedras::Piedras(Jugador* jugador) : Objetivo(NOMBRE, jugador) {
	this -> actualizar();
}

bool Piedras::actualizar(){
	if(!this -> cumplido){
		Material piedras_obtenidas = this -> jugador -> obtener_inventario().obtener_material(NOMBRES_MATERIALES[PIEDRA]);
		if(piedras_obtenidas.obtener_cantidad() >= PIEDRAS_A_OBTENER)
			this -> cumplido = true;
	}
	return this -> cumplido;
}

