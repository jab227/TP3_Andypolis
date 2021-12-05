#include "Piedras.h"

const int PIEDRAS_A_OBTENER = 50e3;

Piedras::Piedras(Jugador* jugador) : Objetivo(jugador) {
	this -> titulo = "Edad de piedra";
	this -> cumplido = false;
}

bool Piedras::actualizar(){
	if(!this -> cumplido){
		Material piedras("piedras", 0);
		this -> jugador -> obtener_inventario() -> buscar_material(piedras);
		if(piedras.obtener_cantidad() >= PIEDRAS_A_OBTENER)
			this -> cumplido = true;
	}
	return this -> cumplido;
}

