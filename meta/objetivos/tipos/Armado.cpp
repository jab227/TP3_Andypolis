#include "Armado.h"

const std::size_t BOMBAS_A_OBTENER = 10;

Armado::Armado(Jugador* jugador) : Objetivo(jugador) {
	this -> titulo = "Armado";
}

bool Armado::actualizar(){
	if(!this -> cumplido){
		Material bombas("bombas", 0);
		this -> jugador -> obtener_inventario() -> buscar_material(bombas);
		if(bombas.obtener_cantidad() >= BOMBAS_A_OBTENER)
			this -> cumplido = true;
	}

	return this -> cumplido;
}
