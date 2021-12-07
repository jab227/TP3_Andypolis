#include "Extremista.h"

const std::size_t BOMBAS_A_COMPRAR = 500;

Extremista::Extremista(Jugador* jugador) : Objetivo(jugador) {
	this -> bombas_compradas = 0;
	Material bombas("bombas", 0);
	this -> jugador -> obtener_inventario() -> buscar_material(bombas);
	this -> bombas_actuales = bombas.obtener_cantidad();
	this -> titulo = "Extremista";
}

bool Extremista::actualizar(){
	if(!this -> cumplido){
		Material bombas("bombas", 0);
		this -> jugador -> obtener_inventario() -> buscar_material(bombas);
		if(bombas.obtener_cantidad() > this -> bombas_actuales)
			this -> bombas_compradas += bombas.obtener_cantidad() - this -> bombas_actuales;

		if(this -> bombas_compradas >= BOMBAS_A_COMPRAR)
			this -> cumplido = true;

		this -> bombas_actuales = bombas.obtener_cantidad();
	}
	return this -> cumplido;
}
