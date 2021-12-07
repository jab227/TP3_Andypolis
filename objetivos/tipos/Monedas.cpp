#include "Monedas.h"

const std::size_t MONEDAS_A_OBTENER = 100e3;
const std::string NOMBRE = "Comprar andypolis";

Monedas::Monedas(Jugador* jugador) : Objetivo(NOMBRE, jugador){
	this -> monedas_juntadas = 0;
	Material monedas = Material("andycoins", 0);
	this -> jugador -> obtener_inventario() -> buscar_material(monedas);
	this -> monedas_actuales = monedas.obtener_cantidad();
}

bool Monedas::actualizar(){
	if(!this -> cumplido){
		Material monedas = Material("andycoins", 0);
		this -> jugador -> obtener_inventario() -> buscar_material(monedas);
		if(monedas.obtener_cantidad() > this -> monedas_actuales)
			this -> monedas_juntadas += monedas.obtener_cantidad() - this -> monedas_actuales;

		if(this -> monedas_juntadas >= MONEDAS_A_OBTENER)
			this -> cumplido = true;

		this -> monedas_actuales = monedas.obtener_cantidad();
	}
	return this -> cumplido;
}
