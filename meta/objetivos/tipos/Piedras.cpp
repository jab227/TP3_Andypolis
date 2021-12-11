#include "Piedras.h"

const std::size_t PIEDRAS_A_OBTENER = 50e3;
const std::string NOMBRE = "Edad de piedra";

Piedras::Piedras(Jugador* jugador) : Objetivo(NOMBRE, jugador) {
	this -> actualizar();
}

Piedras::~Piedras(){ }

bool Piedras::actualizar(){
	if(!this -> cumplido){
<<<<<<< HEAD
		Material piedras_obtenidas = this -> jugador -> obtener_inventario().obtener_material(NOMBRES_MATERIALES[PIEDRA]);
		if(piedras_obtenidas.obtener_cantidad() >= PIEDRAS_A_OBTENER)
=======
		Material piedras = this -> jugador -> obtener_inventario().obtener_material("piedras");
		if(piedras.obtener_cantidad() >= PIEDRAS_A_OBTENER)
>>>>>>> 9764137a50e6a39eb0aaf575344ef3061c31ebd1
			this -> cumplido = true;
	}
	return this -> cumplido;
}

