#include "Monedas.h"

const int MONEDAS_A_OBTENER;

Monedas::Monedas(Jugador* jugador) : Objetivo(jugador){
	this -> monedas_juntadas = 0;
	Material monedas = Material("andycoins", 0);
	this -> jugador -> obtener_inventario() -> buscar_material(monedas);
	this -> monedas_actual = monedas.obtener_cantidad();
	this -> titulo = "Comprar andypolis";
}

bool Monedas::actualizar(){
	Material monedas = Material("andycoins", 0);
	this -> jugador -> obtener_inventario() -> buscar_material(monedas);
	if(monedas.obtener_cantidad() > this -> monedas_actual)
		this -> monedas_juntadas += monedas.obtener_cantidad() - this -> monedas_actual;

	if(this -> monedas_juntadas >= MONEDAS_A_OBTENER)
		this -> cumplido = true;

	this -> monedas_actual = monedas.obtener_cantidad();
	return this -> cumplido;
}
