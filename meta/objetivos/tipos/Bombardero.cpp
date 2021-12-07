#include "Bombardero.h"

const std::size_t BOMBAS_A_USAR = 5;
const std::string NOMBRE = "Bombardero";

Bombardero::Bombardero(Jugador* jugador) : Objetivo(NOMBRE, jugador) {
	this -> bombas_usadas = 0;
	Material bombas = Material("bombas", 0);
	this -> jugador -> obtener_inventario() -> buscar_material(bombas);
	this -> bombas_actuales = bombas.obtener_cantidad();
}

Bombardero::~Bombardero(){ }

bool Bombardero::actualizar(){
	if(!this -> cumplido){
		Material bombas = Material("bombas", 0);
		this -> jugador -> obtener_inventario() -> buscar_material(bombas);
		if(bombas.obtener_cantidad() < this -> bombas_actuales)
			this -> bombas_usadas += this -> bombas_actuales - bombas.obtener_cantidad();

		if(this -> bombas_usadas >= BOMBAS_A_USAR)
			this -> cumplido = true;

		this -> bombas_actuales = bombas.obtener_cantidad();
		}

	return this -> cumplido;
}

