#include "Extremista.h"

const std::size_t BOMBAS_A_COMPRAR = 500;
const std::string NOMBRE ="Extremista";

Extremista::Extremista(Jugador* jugador) : Objetivo(NOMBRE,jugador) {
<<<<<<< HEAD
	this -> bombas_compradas = 0;
	Material bombas = this -> jugador -> obtener_inventario().obtener_material(NOMBRES_MATERIALES[BOMBAS]);
=======
	this -> bombas_compradas = 0; 
	Material bombas = this -> jugador -> obtener_inventario().obtener_material("bombas");
>>>>>>> 9764137a50e6a39eb0aaf575344ef3061c31ebd1
	this -> bombas_actuales = bombas.obtener_cantidad();
}

Extremista::~Extremista(){ }

bool Extremista::actualizar(){
	if(!this -> cumplido){
<<<<<<< HEAD
		Material bombas = this -> jugador -> obtener_inventario().obtener_material(NOMBRES_MATERIALES[BOMBAS]);
=======
		Material bombas = this -> jugador -> obtener_inventario().obtener_material("bombas");
>>>>>>> 9764137a50e6a39eb0aaf575344ef3061c31ebd1
		if(bombas.obtener_cantidad() > this -> bombas_actuales)
			this -> bombas_compradas += bombas.obtener_cantidad() - this -> bombas_actuales;

		if(this -> bombas_compradas >= BOMBAS_A_COMPRAR)
			this -> cumplido = true;

		this -> bombas_actuales = bombas.obtener_cantidad();
	}
	return this -> cumplido;
}
