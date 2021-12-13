#include "CasilleroTransitable.h"
#include <iostream>

Casillero_Transitable::Casillero_Transitable(std::string color): Casillero(color) {
	this -> material = Material();
}


void Casillero_Transitable::agregar_material(Material material){
	this -> material = material;
}

bool Casillero_Transitable::esta_ocupado() const{
	return !(this -> material == Material());
}

std::string Casillero_Transitable::obtener_contenido() const{ 
	std::string material = MATERIAL_VACIO;
	if(this -> esta_ocupado())
		material = this -> material.obtener_nombre();

	return material;
}

Resultado_Chequeos Casillero_Transitable::construir_edificio(Edificio* edificio){
	return CASILLERO_NO_CONSTRUIBLE;
}

bool Casillero_Transitable::es_casillero_transitable(){
	return true;
}

Resultado_Chequeos Casillero_Transitable::demoler_edificio(){
	return CASILLERO_NO_CONSTRUIBLE;
}

Resultado_Chequeos Casillero_Transitable::recoger_material(Material& material_recogido){
	Resultado_Chequeos resultado = NO_MATERIALES;	// No mostrar con mostrar_mensaje_chequeo(). 
	if(this->esta_ocupado()){
		std::cout << "Ha recogido " << material.obtener_cantidad() 
		<< " de " << material.obtener_nombre() << std::endl;
		material_recogido = material;
		material = Material();
		resultado = EXITO;
	}
	return resultado;
}

Resultado_Chequeos Casillero_Transitable::reparar_edificio(bool reparar){ return CASILLERO_NO_CONSTRUIBLE;}

void Casillero_Transitable::saludo_material() const{ this -> material.saludar();}

Resultado_Chequeos Casillero_Transitable::atacar_edificio() {return CASILLERO_NO_CONSTRUIBLE;}
