#include "Armado.h"

const std::size_t BOMBAS_A_OBTENER = 10;
const std::string NOMBRE = "Armado";

Armado::Armado(Jugador* jugador) : Objetivo(NOMBRE, jugador) {
	this -> actualizar();
}

Armado::~Armado(){ }

bool Armado::actualizar(){
	if(!this -> cumplido){
<<<<<<< HEAD
		Material bombas = this -> jugador -> obtener_inventario().obtener_material(NOMBRES_MATERIALES[BOMBAS]);
=======
		Material bombas = this -> jugador -> obtener_inventario().obtener_material("bombas");
>>>>>>> 9764137a50e6a39eb0aaf575344ef3061c31ebd1
		if(bombas.obtener_cantidad() >= BOMBAS_A_OBTENER)
			this -> cumplido = true;
	}
	return this -> cumplido;
}
