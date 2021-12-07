#include "CasilleroTransitable.h"
#include <iostream>

Casillero_Transitable::Casillero_Transitable(std::string color): Casillero(color) {
	this -> material = nullptr;
}

Casillero_Transitable::~Casillero_Transitable() {
	if(this -> esta_ocupado())
		delete this -> material;
}

void Casillero_Transitable::agregar_material(Material* material){
	this -> material = material;
}

//WHY: Potencialmente borrable.
/*
Material* Casillero_Transitable::eliminar_material(){
	Material* material = nullptr;
	if(this -> esta_ocupado()){
		material = this -> material;
		this -> material = nullptr;
	}
	return material;
}
*/

bool Casillero_Transitable::esta_ocupado() const{
	return !(this -> material == nullptr);
}

std::string Casillero_Transitable::obtener_contenido() const{ 
	std::string material = MATERIAL_VACIO;
	if(this -> esta_ocupado())
		material = this -> material -> obtener_nombre();

	return material;
 }


Edificio* Casillero_Transitable::agregar_lista_edificio( Coordenada* coordenada, Lista<Edificio>* &lista_construidos){
	Edificio* edificio = nullptr;
	return edificio;
}

Resultado_Chequeos Casillero_Transitable::construir_edificio(Edificio* edificio){
	return CASILLERO_NO_CONSTRUIBLE;
}

	
//Provisorio
bool Casillero_Transitable::es_casillero_transitable(){
	return true;
}

Resultado_Chequeos Casillero_Transitable::demoler_edificio(){
	return CASILLERO_NO_CONSTRUIBLE;
}

Resultado_Chequeos Casillero_Transitable::recoger_material(Almacen* inventario){
	Resultado_Chequeos resultado = NO_MATERIALES;	// No mostrar con mostrar_mensaje_chequeo(). 
	//Es por si por fuera necesitamos saber si agarro algo.
	//Podriamos retornar el material o imprimir por consola lo que recogió acá.
	if(this->esta_ocupado()){
	// Q: Adaptar
		inventario -> sumar_cantidad_material(material -> obtener_nombre(), material -> obtener_cantidad());
		std::cout << "Ha recogido " << material -> obtener_cantidad() << " de " << material -> obtener_nombre() << std::endl;
		delete material;
		material = nullptr;
		resultado = EXITO;
	}
	return resultado;
}

Resultado_Chequeos Casillero_Transitable::reparar_edificio(){ return CASILLERO_NO_CONSTRUIBLE;}

void Casillero_Transitable::saludo_material() const{ this -> material -> saludar();}

Resultado_Chequeos Casillero_Transitable::atacar_edificio() {return CASILLERO_NO_CONSTRUIBLE;}