#include "Monedas.h"

Monedas::Monedas(Jugador* jugador) : Objetivo(jugador){
	this -> monedas_juntadas = 0;
	this -> monedas_actual = 0;//this -> jugador -> obtener_inventario()
}

