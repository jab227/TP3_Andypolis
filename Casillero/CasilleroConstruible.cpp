#include "CasilleroConstruible.h"
#include "../empresa/Planos.h"
#include <iostream>

Casillero_Construible::Casillero_Construible(): Casillero(VERDE + NEGRO) {
	this -> edificio_ = nullptr;
}

Casillero_Construible::~Casillero_Construible() {
	delete this -> edificio_;
}

Resultado_Chequeos Casillero_Construible::construir_edificio(Edificio* edificio){
	Resultado_Chequeos resultado=CASILLERO_OCUPADO;
	if(!(this -> esta_ocupado())){
		this -> edificio_ = edificio;
		resultado = EXITO;
	}else{
		std::cout <<  "Esta ubicacion esta ocupada por otro edificio." << std::endl;
	}
	return resultado;
}

Resultado_Chequeos Casillero_Construible::demoler_edificio(){
	// Reveer.
	Resultado_Chequeos resultado = SALIR;
	if(this -> esta_ocupado()){
		delete this -> edificio_;
		this -> edificio_ = nullptr;
		resultado = EXITO;
	}
	return resultado;
}

bool Casillero_Construible::esta_ocupado() const{
	return (this -> edificio_ != nullptr);
}

void Casillero_Construible::saludar() const{
	std::cout << "Soy un casillero construible." << std::endl;
	if(this -> esta_ocupado()){
		this -> edificio_ -> saludar();
	}else
		std::cout << "No tengo ningun edificio construido." << std::endl;
}

std::string Casillero_Construible::obtener_contenido() const{
	std::string edificio = EDIFICIO_VACIO; 
	if( this -> esta_ocupado()){
		edificio = this -> edificio_ -> obtener_nombre();
	}
	return edificio;
}

bool Casillero_Construible::es_casillero_transitable(){return false;}


Resultado_Chequeos Casillero_Construible::recoger_material(Material& material_recogido){
	if(esta_ocupado()) material_recogido = edificio_ -> producir_material();
	return EXITO;
}


Resultado_Chequeos Casillero_Construible::reparar_edificio(bool reparar){
	Resultado_Chequeos resultado = NO_EXISTE;
	if(this->esta_ocupado())
		resultado = this -> edificio_ -> reparar(reparar);
	return resultado;
}

Resultado_Chequeos Casillero_Construible::atacar_edificio() {
	Resultado_Chequeos resultado = NO_EXISTE;
	if(this -> esta_ocupado())
		resultado = this -> edificio_ -> disminuir_vida();
	return resultado;
}


void Casillero_Construible::agregar_material(Material material){}

char Casillero_Construible::obtener_identificador(){return TERRENO;}
